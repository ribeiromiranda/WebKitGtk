

#include "php_webkitgtk.h"

#include "ext/standard/base64.h"



// PROPERTIES

// METHODS
PHP_METHOD(WebKitGtkWebResource, __construct);
PHP_METHOD(WebKitGtkWebResource, getData);
PHP_METHOD(WebKitGtkWebResource, getEncoding);
PHP_METHOD(WebKitGtkWebResource, getFrameName);
PHP_METHOD(WebKitGtkWebResource, getMimeType);
PHP_METHOD(WebKitGtkWebResource, getUri);

// METHODS ARGS

// METHOD + ARGS
const zend_function_entry webkitwebresource_class_functions[] = {
	PHP_ME(WebKitGtkWebResource, __construct, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebResource, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebResource, getEncoding, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebResource, getFrameName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebResource, getMimeType, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebResource, getUri, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};



// internal functions
zend_object_value webkitgtk_webresource_new(zend_class_entry *class_type TSRMLS_DC);
void webkitgtk_object_free_storage_webresource(void *object TSRMLS_DC);


static zend_object_handlers webkitgtk_object_handlers_webresource;


PHP_MINIT_FUNCTION(webresource)
{
	zend_class_entry ce_webresource;
	INIT_CLASS_ENTRY(ce_webresource, "WebKitGtkWebResource", webkitwebresource_class_functions);
	ce_webresource.create_object = webkitgtk_webresource_new;
	ce_WebKitGtkWebResource = zend_register_internal_class(&ce_webresource TSRMLS_CC);
	memcpy(&webkitgtk_object_handlers_webresource,
			zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	webkitgtk_object_handlers_webresource.clone_obj = NULL;

	return SUCCESS;
}


zend_object_value webkitgtk_webresource_new(zend_class_entry *class_type TSRMLS_DC)
{
	WebKitWebResource_object *intern;
	zend_object_value retval;

	intern = emalloc(sizeof(WebKitWebResource_object));
	memset(intern, 0, sizeof(WebKitWebResource_object));
	intern->webResource = NULL;

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);


	retval.handle = zend_objects_store_put(intern, (zend_objects_store_dtor_t)zend_objects_destroy_object,
			(zend_objects_free_object_storage_t) webkitgtk_object_free_storage_webresource, NULL TSRMLS_CC);
	retval.handlers = &webkitgtk_object_handlers_webresource;

	return retval;
}

void webkitgtk_object_free_storage_webresource(void *object TSRMLS_DC)
{
	WebKitWebResource_object *intern = (WebKitWebResource_object *)object;

	// FIXME: Trocar para o destroy do webkit
	if (intern->webResource && GTK_IS_WIDGET(intern->webResource)) {
		gtk_widget_destroy(intern->webResource);
	}

	zend_object_std_dtor(&intern->std TSRMLS_CC);
	efree(object);
}


PHP_METHOD(WebKitGtkWebResource, __construct)
{
	// FIXME: Não deixar o client instanciar essa classe
}

PHP_METHOD(WebKitGtkWebResource, getData)
{
	WebKitWebResource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	GString *data = webkit_web_resource_get_data(object->webResource);
	if (data == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(data->str, 1);
}

PHP_METHOD(WebKitGtkWebResource, getEncoding)
{
	WebKitWebResource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	const gchar *encoding = webkit_web_resource_get_encoding(object->webResource);
	if (encoding == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(encoding, 1);
}

PHP_METHOD(WebKitGtkWebResource, getFrameName)
{
	WebKitWebResource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	gchar *data = webkit_web_resource_get_frame_name(object->webResource);
	if (data == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(data, 1);
}

PHP_METHOD(WebKitGtkWebResource, getMimeType)
{
	WebKitWebResource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	gchar *data=  webkit_web_resource_get_mime_type(object->webResource);
	if (data == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(data, 1);
}

PHP_METHOD(WebKitGtkWebResource, getUri)
{
	WebKitWebResource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	gchar *data =  webkit_web_resource_get_uri(object->webResource);
	if (data == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(data, 1);
}
