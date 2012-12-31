

#include "php_webkitgtk.h"


// PROPERTIES


// METHODS
PHP_METHOD(WebKitGtkWebSettings, __construct);
PHP_METHOD(WebKitGtkWebSettings, get_user_agent );


// METHODS ARGS
ZEND_BEGIN_ARG_INFO_EX(arginfo_webkitgtkwebsettings_get_user_agent, 0, 0, 1)
	ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

// METHOD + ARGS
const zend_function_entry webkitwebsettings_class_functions[] = {
	PHP_ME(WebKitGtkWebSettings, __construct, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebSettings, get_user_agent, arginfo_webkitgtkwebsettings_get_user_agent, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


static zend_object_handlers webkitgtk_object_handlers_websettings;

// internal functions
zend_object_value webkitgtk_websettings_new(zend_class_entry *class_type TSRMLS_DC);
void webkitgtk_object_free_storage_websettings(void *object TSRMLS_DC);


PHP_MINIT_FUNCTION(websettings)
{
	zend_class_entry ce_websettingsgtk;
	INIT_CLASS_ENTRY(ce_websettingsgtk, "WebKitGtkWebSettings", webkitwebsettings_class_functions);
	ce_websettingsgtk.create_object = webkitgtk_websettings_new;
	ce_WebKitGtkWebSettings = zend_register_internal_class(&ce_websettingsgtk TSRMLS_CC);
	memcpy(&webkitgtk_object_handlers_websettings,
			zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	webkitgtk_object_handlers_websettings.clone_obj = NULL;

	return SUCCESS;
}


zend_object_value webkitgtk_websettings_new(zend_class_entry *class_type TSRMLS_DC)
{
	WebKitWebSettings_object *intern;
	zend_object_value retval;

	intern = emalloc(sizeof(WebKitWebSettings_object));
	memset(intern, 0, sizeof(WebKitWebSettings_object));
	intern->webSettings = NULL;

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);


	retval.handle = zend_objects_store_put(intern, (zend_objects_store_dtor_t)zend_objects_destroy_object,
			(zend_objects_free_object_storage_t) webkitgtk_object_free_storage_websettings, NULL TSRMLS_CC);
	retval.handlers = &webkitgtk_object_handlers_websettings;

	return retval;
}

void webkitgtk_object_free_storage_websettings(void *object TSRMLS_DC)
{
	WebKitWebSettings_object *intern = (WebKitWebSettings_object *)object;

	if (intern->webSettings && GTK_IS_WIDGET(intern->webSettings)) {
		gtk_widget_destroy(intern->webSettings);
	}

	zend_object_std_dtor(&intern->std TSRMLS_CC);
	efree(object);
}


PHP_METHOD(WebKitGtkWebSettings, __construct)
{
	// Initialize GTK+
	int argc = 0;
	char *argv[] = {};
	gtk_init(&argc, &argv);

	//WebKitWebSettings_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	//object->webSettings = WEBKIT_WEB_VIEW(webkit_web_view_new());
}

PHP_METHOD(WebKitGtkWebSettings, get_user_agent )
{

}
