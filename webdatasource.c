

#include "php_webkitgtk.h"

#include "ext/standard/base64.h"



// PROPERTIES

// METHODS
PHP_METHOD(WebKitGtkWebDataSource, __construct);
PHP_METHOD(WebKitGtkWebDataSource, getData);
PHP_METHOD(WebKitGtkWebDataSource, getEncoding);
PHP_METHOD(WebKitGtkWebDataSource, getInitialRequest);
PHP_METHOD(WebKitGtkWebDataSource, getMainResource);
PHP_METHOD(WebKitGtkWebDataSource, getRequest);
PHP_METHOD(WebKitGtkWebDataSource, getSubResources);
PHP_METHOD(WebKitGtkWebDataSource, getUnreachableUri);
PHP_METHOD(WebKitGtkWebDataSource, getWebFrame);
PHP_METHOD(WebKitGtkWebDataSource, isLoading);

// METHODS ARGS

// METHOD + ARGS
const zend_function_entry webkitwebdatasource_class_functions[] = {
	PHP_ME(WebKitGtkWebDataSource, __construct, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebDataSource, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebDataSource, getEncoding, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebDataSource, getInitialRequest, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebDataSource, getMainResource, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebDataSource, getRequest, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebDataSource, getSubResources, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebDataSource, getUnreachableUri, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebDataSource, getWebFrame, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkWebDataSource, isLoading, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};



// internal functions
zend_object_value webkitgtk_webdatasource_new(zend_class_entry *class_type TSRMLS_DC);
void webkitgtk_object_free_storage_webdatasource(void *object TSRMLS_DC);


static zend_object_handlers webkitgtk_object_handlers_webdatasource;


PHP_MINIT_FUNCTION(webdatasource)
{
	zend_class_entry ce_webdatasource;
	INIT_CLASS_ENTRY(ce_webdatasource, "WebKitGtkWebDataSource", webkitwebdatasource_class_functions);
	ce_webdatasource.create_object = webkitgtk_webdatasource_new;
	ce_WebKitGtkWebDataSource = zend_register_internal_class(&ce_webdatasource TSRMLS_CC);
	memcpy(&webkitgtk_object_handlers_webdatasource,
			zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	webkitgtk_object_handlers_webdatasource.clone_obj = NULL;

	return SUCCESS;
}


zend_object_value webkitgtk_webdatasource_new(zend_class_entry *class_type TSRMLS_DC)
{
	WebKitWebDataSource_object *intern;
	zend_object_value retval;

	intern = emalloc(sizeof(WebKitWebDataSource_object));
	memset(intern, 0, sizeof(WebKitWebDataSource_object));
	intern->webDataSource = NULL;

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);


	retval.handle = zend_objects_store_put(intern, (zend_objects_store_dtor_t)zend_objects_destroy_object,
			(zend_objects_free_object_storage_t) webkitgtk_object_free_storage_webdatasource, NULL TSRMLS_CC);
	retval.handlers = &webkitgtk_object_handlers_webdatasource;

	return retval;
}

void webkitgtk_object_free_storage_webdatasource(void *object TSRMLS_DC)
{
	WebKitWebDataSource_object *intern = (WebKitWebDataSource_object *)object;

	// FIXME: Trocar para o destroy do webkit
	if (intern->webDataSource && GTK_IS_WIDGET(intern->webDataSource)) {
		gtk_widget_destroy(intern->webDataSource);
	}


	zend_object_std_dtor(&intern->std TSRMLS_CC);
	efree(object);
}


PHP_METHOD(WebKitGtkWebDataSource, __construct)
{
	// FIXME: Não deixar o client instanciar essa classe
}

PHP_METHOD(WebKitGtkWebDataSource, getData)
{
	WebKitWebDataSource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	GString *data = webkit_web_data_source_get_data(object->webDataSource);
	RETURN_STRING(data->str, 1);
}

PHP_METHOD(WebKitGtkWebDataSource, getEncoding)
{
	WebKitWebDataSource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	const gchar *encoding = webkit_web_data_source_get_encoding(object->webDataSource);
	if (encoding == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(encoding, 1);
}

PHP_METHOD(WebKitGtkWebDataSource, getInitialRequest)
{
	WebKitWebDataSource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
}

PHP_METHOD(WebKitGtkWebDataSource, getMainResource)
{
	WebKitWebDataSource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	WebKitWebResource *resource = webkit_web_data_source_get_main_resource(object->webDataSource);

	php_webkitgtk_instantiate(ce_WebKitGtkWebResource, return_value TSRMLS_CC);
	WebKitWebResource_object *webResource = zend_object_store_get_object(return_value TSRMLS_CC);
	webResource->webResource = resource;
}

PHP_METHOD(WebKitGtkWebDataSource, getRequest)
{
	WebKitNetworkRequest_object *networkRequest;

	WebKitWebDataSource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);

	php_webkitgtk_instantiate(ce_WebKitGtkNetworkRequest, return_value TSRMLS_CC);
	networkRequest = zend_object_store_get_object(return_value TSRMLS_CC);
	networkRequest->networkRequest = webkit_web_data_source_get_request(object->webDataSource);
}

PHP_METHOD(WebKitGtkWebDataSource, getSubResources)
{
	WebKitWebDataSource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	GList *subResources = webkit_web_data_source_get_subresources(object->webDataSource);

	array_init(return_value);

	while(subResources) {
		zval *webResource;
		WebKitWebResource_object *webResource_object;

		ALLOC_INIT_ZVAL(webResource);
		Z_TYPE_P(webResource) = IS_OBJECT;


		php_webkitgtk_instantiate(ce_WebKitGtkWebResource, webResource TSRMLS_CC);
		webResource_object = zend_object_store_get_object(webResource TSRMLS_CC);
		webResource_object->webResource = (WebKitWebResource *) subResources->data;

		add_next_index_zval(return_value, webResource);

		subResources = subResources->next;
	}
}

PHP_METHOD(WebKitGtkWebDataSource, getUnreachableUri)
{
	WebKitWebDataSource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	const gchar *uri = webkit_web_data_source_get_unreachable_uri(object->webDataSource);
	if (uri == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(uri, 1);
}

PHP_METHOD(WebKitGtkWebDataSource, getWebFrame)
{
	WebKitWebDataSource_object *object;
	WebKitWebFrame *webFrameLocal;

	WebKitWebFrame_object *webFramePHPOrig;

	object = zend_object_store_get_object(getThis() TSRMLS_CC);
	webFramePHPOrig = zend_object_store_get_object(object->zWebFrame TSRMLS_CC);

	webFrameLocal = webkit_web_data_source_get_web_frame(object->webDataSource);

	if (webFrameLocal == webFramePHPOrig->webFrame) {
		*return_value = *object->zWebFrame;
	} else {
		// FIXME: Não pode ser diferente;
	}
}

PHP_METHOD(WebKitGtkWebDataSource, isLoading)
{
	WebKitWebDataSource_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	RETURN_BOOL(webkit_web_data_source_is_loading(object->webDataSource));
}
