--- ../mod_zip-74ef235/ngx_http_zip_module.c
+++ ../mod_zip-74ef235/ngx_http_zip_module.c
@@ -67,12 +67,14 @@ static ngx_command_t  ngx_http_zip_commands[] = {
 	  offsetof(ngx_http_zip_conf_t, enable),
 	  NULL },
 
+#ifdef NGX_ZIP_HAVE_ICONV
 	{ ngx_string("zip_charset"),
 	  NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
 	  ngx_conf_set_str_slot,
 	  NGX_HTTP_LOC_CONF_OFFSET,
 	  offsetof(ngx_http_zip_conf_t, charset),
 	  NULL },
+#endif
 
 	{ ngx_string("zip_name_separator"),
 	  NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
@@ -237,7 +239,8 @@ ngx_http_zip_subrequest_header_filter(ngx_http_request_t *r)
 
     ctx = ngx_http_get_module_ctx(r->main, ngx_http_zip_module);
     if (ctx != NULL) {
-        if (r->headers_out.status != NGX_HTTP_OK) {
+        if (r->headers_out.status != NGX_HTTP_OK &&
+                r->headers_out.status != NGX_HTTP_PARTIAL_CONTENT) {
             ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                     "mod_zip: a subrequest returned %d, aborting...",
                     r->headers_out.status);
@@ -575,6 +578,9 @@ ngx_http_zip_send_piece(ngx_http_request_t *r, ngx_http_zip_ctx_t *ctx, ngx_http
     ngx_http_zip_sr_ctx_t *sr_ctx;
     ngx_int_t rc;
 
+    off_t start, end;
+    ngx_str_t *args;
+
     if (piece->type == zip_header_piece) {
         if ((link = ngx_http_zip_file_header_chain_link(r, ctx, piece, range)) == NULL)
             return NGX_ERROR;
@@ -600,8 +606,30 @@ ngx_http_zip_send_piece(ngx_http_request_t *r, ngx_http_zip_ctx_t *ctx, ngx_http
                 return NGX_AGAIN;
             }
         }
-        rc = ngx_http_subrequest(r, &piece->file->uri, &piece->file->args, &sr, NULL, NGX_HTTP_SUBREQUEST_WAITED);
-        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "mod_zip: subrequest for \"%V?%V\" result %d, allocating some mem on main request's pool", &piece->file->uri, &piece->file->args, rc);
+
+        start = range && range->start > piece->range.start ? range->start - piece->range.start : 0;
+        end   = range && range->end   < piece->range.end   ? range->end   - piece->range.start : 0;
+
+        if (end < 0 || end && end < start) {
+            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "mod_zip: invalid range end: %O", end);
+            end = 0;
+        }
+
+        if (start || end) {
+            args = ngx_palloc(r->pool, sizeof(ngx_str_t));
+            args->data = ngx_palloc(r->pool, piece->file->args.len + 64);
+            args->len = ngx_cpymem(args->data, piece->file->args.data, piece->file->args.len) - args->data;
+
+            if (start)
+                args->len = ngx_sprintf(args->data + args->len, "&slice_start=%O", start) - args->data;
+            if (end)
+                args->len = ngx_sprintf(args->data + args->len, "&slice_end=%O", end) - args->data;
+        } else {
+            args = &piece->file->args;
+        }
+
+        rc = ngx_http_subrequest(r, &piece->file->uri, args, &sr, NULL, NGX_HTTP_SUBREQUEST_WAITED);
+        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "mod_zip: subrequest for \"%V?%V\" result %d, allocating some mem on main request's pool", &piece->file->uri, args, rc);
         if (rc == NGX_ERROR) {
             return NGX_ERROR;
         }
@@ -610,10 +638,10 @@ ngx_http_zip_send_piece(ngx_http_request_t *r, ngx_http_zip_ctx_t *ctx, ngx_http
             return NGX_ERROR;
 
         sr_ctx->requesting_file = piece->file;
-        sr_ctx->subrequest_pos = piece->range.start;
+        sr_ctx->subrequest_pos = piece->range.start + start;
         sr_ctx->range = range;
         ngx_http_set_ctx(sr, sr_ctx, ngx_http_zip_module);
-        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "mod_zip: subrequest for \"%V?%V\" result %d", &piece->file->uri, &piece->file->args, rc);
+        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "mod_zip: subrequest for \"%V?%V\" result %d", &piece->file->uri, args, rc);
         if (ctx->wait == NULL) {
             ctx->wait = sr;
             return NGX_AGAIN;   // must be NGX_AGAIN
