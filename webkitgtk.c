#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include "php_webkitgtk.h"

PHPAPI zval *php_webkitgtk_instantiate(zend_class_entry *pce, zval *object TSRMLS_DC)
{
	Z_TYPE_P(object) = IS_OBJECT;
	object_init_ex(object, pce);
	Z_SET_REFCOUNT_P(object, 1);
	Z_UNSET_ISREF_P(object);
	return object;
}


zend_module_entry webkitgtk_module_entry = {
    STANDARD_MODULE_HEADER,
    "webkitgtk",
    NULL, //webkitgtk_functions, /* Function Entries */
    PHP_MINIT(webkitgtk), /* Module Init */
    NULL, /* Module shtudown */
    NULL, /* Requet init */
    NULL, /* Request shutdown */
    NULL,
    PHP_WEBKITGTK_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_WEBKITGTK
ZEND_GET_MODULE(webkitgtk)
#endif


PHP_MINIT_FUNCTION(webkitgtk) {

	PHP_MINIT(webview)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(webframe)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(webdatasource)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(webresource)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(websettings)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(networkrequest)(INIT_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
