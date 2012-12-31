

#include "php_webkitgtk.h"

#include "ext/standard/base64.h"



// PROPERTIES

// METHODS
PHP_METHOD(WebKitGtkNetworkRequest, __construct);
PHP_METHOD(WebKitGtkNetworkRequest, getUri );
PHP_METHOD(WebKitGtkNetworkRequest, getMessage);
PHP_METHOD(WebKitGtkNetworkRequest, setUri);

// METHODS ARGS
ZEND_BEGIN_ARG_INFO_EX(arginfo_webkitgtknetworkrequest_set_uri, 0, 0, 1)
	ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

// METHOD + ARGS
const zend_function_entry webkitnetworkrequest_class_functions[] = {
	PHP_ME(WebKitGtkNetworkRequest, __construct, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkNetworkRequest, getUri, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkNetworkRequest, getMessage, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(WebKitGtkNetworkRequest, setUri, arginfo_webkitgtknetworkrequest_set_uri, ZEND_ACC_PUBLIC)
	PHP_FE_END
};



// internal functions
zend_object_value webkitgtk_networkrequest_new(zend_class_entry *class_type TSRMLS_DC);
void webkitgtk_object_free_storage_networkrequest(void *object TSRMLS_DC);


static zend_object_handlers webkitgtk_object_handlers_networkrequest;


PHP_MINIT_FUNCTION(networkrequest)
{
	zend_class_entry ce_networkrequest;
	INIT_CLASS_ENTRY(ce_networkrequest, "WebKitGtkNetworkRequest", webkitnetworkrequest_class_functions);
	ce_networkrequest.create_object = webkitgtk_networkrequest_new;
	ce_WebKitGtkNetworkRequest = zend_register_internal_class(&ce_networkrequest TSRMLS_CC);
	memcpy(&webkitgtk_object_handlers_networkrequest,
			zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	webkitgtk_object_handlers_networkrequest.clone_obj = NULL;

	return SUCCESS;
}


zend_object_value webkitgtk_networkrequest_new(zend_class_entry *class_type TSRMLS_DC)
{
	WebKitNetworkRequest_object *intern;
	zend_object_value retval;

	intern = emalloc(sizeof(WebKitNetworkRequest_object));
	memset(intern, 0, sizeof(WebKitNetworkRequest_object));
	intern->networkRequest = NULL;

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);


	retval.handle = zend_objects_store_put(intern, (zend_objects_store_dtor_t)zend_objects_destroy_object,
			(zend_objects_free_object_storage_t) webkitgtk_object_free_storage_networkrequest, NULL TSRMLS_CC);
	retval.handlers = &webkitgtk_object_handlers_networkrequest;

	return retval;
}

void webkitgtk_object_free_storage_networkrequest(void *object TSRMLS_DC)
{
	WebKitNetworkRequest_object *intern = (WebKitNetworkRequest_object *)object;

	// FIXME: Trocar para o destroy do webkit
	if (intern->networkRequest && GTK_IS_WIDGET(intern->networkRequest)) {
		gtk_widget_destroy(intern->networkRequest);
	}


	zend_object_std_dtor(&intern->std TSRMLS_CC);
	efree(object);
}


PHP_METHOD(WebKitGtkNetworkRequest, __construct)
{
	// FIXME: Não deixar o client instanciar essa classe
}

PHP_METHOD(WebKitGtkNetworkRequest, getUri )
{

	WebKitNetworkRequest_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	gchar *data = webkit_network_request_get_uri(object->networkRequest);
	RETURN_STRING(data, 1);
}

PHP_METHOD(WebKitGtkNetworkRequest, getMessage)
{
	WebKitNetworkRequest_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	gchar *data = webkit_network_request_get_message(object->networkRequest);
	RETURN_STRING(data, 1);
}

PHP_METHOD(WebKitGtkNetworkRequest, setUri)
{
	char *uri;
	int *uri_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &uri, &uri_len) == FAILURE) {
		RETURN_FALSE;
	}
	WebKitNetworkRequest_object *object = zend_object_store_get_object(getThis() TSRMLS_CC);
	webkit_network_request_set_uri(object->networkRequest, uri);
}
