#ifndef PHP_WEBKITGTK_H
#define PHP_WEBKITGTK_H 1

#define PHP_WEBKITGTK_VERSION "1.0"

#include "php.h"

#include <gtk/gtk.h>
#include <webkit/webkit.h>


extern zend_module_entry webkitgtk_module_entry;
#define phpext_webkitgtk_ptr &webkitgtk_module_entry


// class
zend_class_entry *ce_WebKitGtkWebView;
zend_class_entry *ce_WebKitGtkWebFrame;
zend_class_entry *ce_WebKitGtkWebDataSource;
zend_class_entry *ce_WebKitGtkWebResource;
zend_class_entry *ce_WebKitGtkWebSettings;
zend_class_entry *ce_WebKitGtkNetworkRequest;


typedef struct _WebKitWebView_object WebKitWebView_object;
typedef struct _WebKitWebFrame_object WebKitWebFrame_object;
typedef struct _WebKitWebDataSource_object WebKitWebDataSource_object;
typedef struct _WebKitWebResource_object WebKitWebResource_object;
typedef struct _WebKitWebSettings_object WebKitWebSettings_object;
typedef struct _WebKitNetworkRequest_object WebKitNetworkRequest_object;


typedef struct _WebKitWebView_object {
	zend_object   std;
	WebKitWebView *webView;
	int success;
	HashTable    *props;
};

typedef struct _WebKitWebFrame_object {
	zend_object   std;
	WebKitWebFrame *webFrame;
	HashTable    *props;
};

typedef struct _WebKitWebDataSource_object {
	zend_object   std;
	WebKitWebDataSource *webDataSource;
	zval *zWebFrame;
	HashTable    *props;
};

typedef struct _WebKitWebResource_object {
	zend_object   std;
	WebKitWebResource *webResource;
	HashTable    *props;
};

typedef struct _WebKitWebSettings_object {
	zend_object   std;
	WebKitWebSettings *webSettings;
	HashTable    *props;
};

typedef struct _WebKitNetworkRequest_object {
	zend_object   std;
	WebKitNetworkRequest *networkRequest;
	HashTable    *props;
};

PHP_MINIT_FUNCTION(webkitgtk);



PHPAPI zval *php_webkitgtk_instantiate(zend_class_entry *pce, zval *object TSRMLS_DC);


#endif
