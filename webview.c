

#include "php_webkitgtk.h"


// PROPERTIES


// METHODS
PHP_METHOD(WebKitGtkWebView, __construct);
PHP_METHOD(WebKitGtkWebView, open);
PHP_METHOD(WebKitGtkWebView, getMainFrame);

// METHODS ARGS
ZEND_BEGIN_ARG_INFO_EX(arginfo_webkitgtkwebview_open, 0, 0, 1)
	ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

// METHOD + ARGS
const zend_function_entry webkitwebview_class_functions[] = {
	PHP_ME(WebKitGtkWebView, __construct, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebView, open, arginfo_webkitgtkwebview_open, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebView, getMainFrame, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


static zend_object_handlers webkitgtk_object_handlers_webview;

// internal functions
zend_object_value webkitgtk_webview_new(zend_class_entry *class_type TSRMLS_DC);
void webkitgtk_object_free_storage_webview(void *object TSRMLS_DC);
static void loadStatusCb(WebKitWebView *web_view, GParamSpec *pspec, void* context);


PHP_MINIT_FUNCTION(webview)
{
	zend_class_entry ce_webviewgtk;
	INIT_CLASS_ENTRY(ce_webviewgtk, "WebKitGtkWebView", webkitwebview_class_functions);
	ce_webviewgtk.create_object = webkitgtk_webview_new;
	ce_WebKitGtkWebView = zend_register_internal_class(&ce_webviewgtk TSRMLS_CC);
	memcpy(&webkitgtk_object_handlers_webview,
			zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	webkitgtk_object_handlers_webview.clone_obj = NULL;

	return SUCCESS;
}


zend_object_value webkitgtk_webview_new(zend_class_entry *class_type TSRMLS_DC)
{
	WebKitWebView_object *intern;
	zend_object_value retval;

	intern = emalloc(sizeof(WebKitWebView_object));
	memset(intern, 0, sizeof(WebKitWebView_object));
	intern->webView = NULL;

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);


	retval.handle = zend_objects_store_put(intern, (zend_objects_store_dtor_t)zend_objects_destroy_object,
			(zend_objects_free_object_storage_t) webkitgtk_object_free_storage_webview, NULL TSRMLS_CC);
	retval.handlers = &webkitgtk_object_handlers_webview;

	return retval;
}

void webkitgtk_object_free_storage_webview(void *object TSRMLS_DC)
{
	WebKitWebView_object *intern = (WebKitWebView_object *)object;

	if (intern->webView) {
		gtk_widget_destroy(intern->webView);
	}

	zend_object_std_dtor(&intern->std TSRMLS_CC);
	efree(object);
}


PHP_METHOD(WebKitGtkWebView, __construct)
{
	// Initialize GTK+
	int argc = 0;
	char *argv[] = {};
	gtk_init(&argc, &argv);

	WebKitWebView_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	object->webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
}

PHP_METHOD(WebKitGtkWebView, open)
{
	//if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|bll", &str, &str_len, &assoc, &depth, &options) == FAILURE) {
	//	return;
	//}
	WebKitWebView_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	webkit_web_view_open(object->webView, "http://google.com.br");
	g_signal_connect(object->webView, "notify::load-status", G_CALLBACK(loadStatusCb), object);
	//php_printf(" open \n");
	gtk_main();

	RETURN_BOOL(object->success);
}

static void loadStatusCb(WebKitWebView *web_view, GParamSpec *pspec, void* context)
{
	WebKitLoadStatus status = webkit_web_view_get_load_status(web_view);

	WebKitWebView_object *webView_object = (WebKitWebView_object *) context;

	//GObject *object = G_OBJECT(web_view);

	//g_assert(web_view == context);
	//g_object_freeze_notify(object);

	switch (status) {
	case WEBKIT_LOAD_FINISHED:
		//printf("WEBKIT_LOAD_FINISHED\n");
		//handleLoadFinished(web_view, context);
		webView_object->success = TRUE;
		gtk_main_quit();
		break;
	case WEBKIT_LOAD_PROVISIONAL:
		//php_printf("WEBKIT_LOAD_PROVISIONAL\n");
		//handleLoadProvisional(web_view, context);
		break;
	case WEBKIT_LOAD_COMMITTED:
		//php_printf("WEBKIT_LOAD_COMMITTED\n");
		//handleLoadCommitted(web_view, context);
		break;
	case WEBKIT_LOAD_FIRST_VISUALLY_NON_EMPTY_LAYOUT:
		//php_printf("WEBKIT_LOAD_FIRST_VISUALLY_NON_EMPTY_LAYOUT\n");
		//handleLoadNonEmptyLayout(web_view, context);
		break;
	case WEBKIT_LOAD_FAILED:
		//php_printf("WEBKIT_LOAD_FAILED\n");
		//handleLoadFailed(web_view, context);
		webView_object->success = FALSE;
		gtk_main_quit();
		break;
	default:
		break;
	}
	//g_object_thaw_notify(object);
}

PHP_METHOD(WebKitGtkWebView, getMainFrame) {
	WebKitWebFrame_object *webFrame;

	WebKitWebView_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);

	php_webkitgtk_instantiate(ce_WebKitGtkWebFrame, return_value TSRMLS_CC);
	webFrame = zend_object_store_get_object(return_value TSRMLS_CC);

}
