--- etc/afpd/volume.c.orig	2016-07-20 13:19:58 UTC
+++ etc/afpd/volume.c
@@ -71,6 +71,8 @@ static long long int get_tm_bandsize(const char *path)
     char buf[512];
     long long int bandsize = -1;
 
+    become_root();
+
     EC_NULL_LOGSTR( file = fopen(path, "r"),
                     "get_tm_bandsize(\"%s\"): %s",
                     path, strerror(errno) );
@@ -90,6 +92,9 @@ EC_CLEANUP:
     if (file)
         fclose(file);
     LOG(log_debug, logtype_afpd, "get_tm_bandsize(\"%s\"): bandsize: %lld", path, bandsize);
+
+    unbecome_root();
+
     return bandsize;
 }
 
@@ -106,6 +111,8 @@ static long long int get_tm_bands(const char *path)
     DIR *dir = NULL;
     const struct dirent *entry;
 
+    become_root();
+
     EC_NULL( dir = opendir(path) );
 
     while ((entry = readdir(dir)) != NULL)
@@ -115,6 +122,9 @@ static long long int get_tm_bands(const char *path)
 EC_CLEANUP:
     if (dir)
         closedir(dir);
+
+    unbecome_root();
+
     if (ret != 0)
         return -1;
     return count;
