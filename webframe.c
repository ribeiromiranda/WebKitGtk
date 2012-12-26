

#include "php_webkitgtk.h"





// PROPERTIES

// METHODS
PHP_METHOD(WebKitGtkWebFrame, __construct);
PHP_METHOD(WebKitGtkWebFrame, getDataSource);

// METHODS ARGS

// METHOD + ARGS
const zend_function_entry webkitwebframe_class_functions[] = {
	PHP_ME(WebKitGtkWebFrame, __construct, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebFrame, getDataSource, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};



// internal functions
zend_object_value webkitgtk_webframe_new(zend_class_entry *class_type TSRMLS_DC);
void webkitgtk_object_free_storage_webframe(void *object TSRMLS_DC);


static zend_object_handlers webkitgtk_object_handlers_webframe;


PHP_MINIT_FUNCTION(webframe)
{
	zend_class_entry ce_webframe;
	INIT_CLASS_ENTRY(ce_webframe, "WebKitGtkWebFrame", webkitwebframe_class_functions);
	ce_webframe.create_object = webkitgtk_webframe_new;
	ce_WebKitGtkWebFrame = zend_register_internal_class(&ce_webframe TSRMLS_CC);
	memcpy(&webkitgtk_object_handlers_webframe,
			zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	webkitgtk_object_handlers_webframe.clone_obj = NULL;

	return SUCCESS;
}


zend_object_value webkitgtk_webframe_new(zend_class_entry *class_type TSRMLS_DC)
{
	WebKitWebFrame_object *intern;
	zend_object_value retval;

	intern = emalloc(sizeof(WebKitWebFrame_object));
	memset(intern, 0, sizeof(WebKitWebFrame_object));
	intern->webFrame = NULL;

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);


	retval.handle = zend_objects_store_put(intern, (zend_objects_store_dtor_t)zend_objects_destroy_object,
			(zend_objects_free_object_storage_t) webkitgtk_object_free_storage_webframe, NULL TSRMLS_CC);
	retval.handlers = &webkitgtk_object_handlers_webframe;

	return retval;
}

void webkitgtk_object_free_storage_webframe(void *object TSRMLS_DC)
{
	WebKitWebFrame_object *intern = (WebKitWebFrame_object *)object;

	if (intern->webFrame) {
		gtk_widget_destroy(intern->webFrame);
	}

	zend_object_std_dtor(&intern->std TSRMLS_CC);
	efree(object);
}


PHP_METHOD(WebKitGtkWebFrame, __construct)
{

	//WebKitWebFrame *mainFrame = webkit_web_view_get_main_frame(object->webFrame);
	//mainFrame
}

PHP_METHOD(WebKitGtkWebFrame, getDataSource)
{
	//WebKitWebDataSource *dataSource = webkit_web_frame_get_data_source();
	//php_printf(" saida %s\n", webkit_web_data_source_get_data(dataSource)->str);

	//WebKitWebResource *mainResource = webkit_web_data_source_get_main_resource(dataSource);
	//if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|bll", &str, &str_len, &assoc, &depth, &options) == FAILURE) {
	//	return;
	//}
}
