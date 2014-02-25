
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/hash.h"
#include "kernel/string.h"
#include "ext/spl/spl_exceptions.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Db\Adapter
 *
 * Base class for Phalcon\Db adapters
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Adapter) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Db, Adapter, phalcon, db_adapter, phalcon_db_adapter_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * Event Manager
	 *
	 * @var Phalcon\Events\Manager
	 */
	zend_declare_property_null(phalcon_db_adapter_ce, SL("_eventsManager"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Descriptor used to connect to a database
	 *
	 * @var stdClass
	 */
	zend_declare_property_null(phalcon_db_adapter_ce, SL("_descriptor"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Name of the dialect used
	 */
	zend_declare_property_null(phalcon_db_adapter_ce, SL("_dialectType"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Type of database system the adapter is used for
	 */
	zend_declare_property_null(phalcon_db_adapter_ce, SL("_type"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Dialect instance
	 */
	zend_declare_property_null(phalcon_db_adapter_ce, SL("_dialect"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Active connection ID
	 *
	 * @var long
	 */
	zend_declare_property_null(phalcon_db_adapter_ce, SL("_connectionId"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Active SQL Statement
	 *
	 * @var string
	 */
	zend_declare_property_null(phalcon_db_adapter_ce, SL("_sqlStatement"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Active SQL bound parameter variables
	 *
	 * @var string
	 */
	zend_declare_property_null(phalcon_db_adapter_ce, SL("_sqlVariables"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Active SQL Bind Types
	 *
	 * @var string
	 */
	zend_declare_property_null(phalcon_db_adapter_ce, SL("_sqlBindTypes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(phalcon_db_adapter_ce, SL("_transactionLevel"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(phalcon_db_adapter_ce, SL("_transactionsWithSavepoints"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Connection ID
	 */
	zend_declare_property_long(phalcon_db_adapter_ce, SL("_connectionConsecutive"), 0, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_class_implements(phalcon_db_adapter_ce TSRMLS_CC, 1, phalcon_events_eventsawareinterface_ce);
	return SUCCESS;

}

/**
 * Name of the dialect used
 */
PHP_METHOD(Phalcon_Db_Adapter, getDialectType) {


	RETURN_MEMBER(this_ptr, "_dialectType");

}

/**
 * Type of database system the adapter is used for
 */
PHP_METHOD(Phalcon_Db_Adapter, getType) {


	RETURN_MEMBER(this_ptr, "_type");

}

/**
 * Active SQL bound parameter variables
 *
 * @var string
 */
PHP_METHOD(Phalcon_Db_Adapter, getSqlVariables) {


	RETURN_MEMBER(this_ptr, "_sqlVariables");

}

/**
 * Phalcon\Db\Adapter constructor
 *
 * @param array descriptor
 */
PHP_METHOD(Phalcon_Db_Adapter, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_class_entry *_2;
	zval *descriptor, *dialectClass, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &descriptor);



	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, 0);
	zephir_update_property_this(this_ptr, SL("_connectionId"), _0 TSRMLS_CC);
	ZEPHIR_OBS_VAR(dialectClass);
	if (!(zephir_array_isset_string_fetch(&dialectClass, descriptor, SS("dialectClass"), 0 TSRMLS_CC))) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialectType"), PH_NOISY_CC);
		ZEPHIR_INIT_BNVAR(dialectClass);
		ZEPHIR_CONCAT_SV(dialectClass, "phalcon\\db\\dialect\\", _0);
	}
	if (Z_TYPE_P(dialectClass) == IS_STRING) {
		ZEPHIR_INIT_VAR(_1);
		_2 = zend_fetch_class(Z_STRVAL_P(dialectClass), Z_STRLEN_P(dialectClass), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(_1, _2);
		if (zephir_has_constructor(_1 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL);
			zephir_check_call_status();
		}
		zephir_update_property_this(this_ptr, SL("_dialect"), _1 TSRMLS_CC);
	}
	zephir_update_property_this(this_ptr, SL("_descriptor"), descriptor TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets the event manager
 *
 * @param Phalcon\Events\ManagerInterface eventsManager
 */
PHP_METHOD(Phalcon_Db_Adapter, setEventsManager) {

	zval *eventsManager;

	zephir_fetch_params(0, 1, 0, &eventsManager);



	if (!(zephir_instance_of_ev(eventsManager, phalcon_events_managerinterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STRW(spl_ce_InvalidArgumentException, "Parameter 'eventsManager' must be an instance of 'Phalcon\\Events\\ManagerInterface'");
		return;
	}
	zephir_update_property_this(this_ptr, SL("_eventsManager"), eventsManager TSRMLS_CC);

}

/**
 * Returns the internal event manager
 *
 * @return Phalcon\Events\ManagerInterface
 */
PHP_METHOD(Phalcon_Db_Adapter, getEventsManager) {


	RETURN_MEMBER(this_ptr, "_eventsManager");

}

/**
 * Sets the dialect used to produce the SQL
 *
 * @param Phalcon\Db\DialectInterface
 */
PHP_METHOD(Phalcon_Db_Adapter, setDialect) {

	zval *dialect;

	zephir_fetch_params(0, 1, 0, &dialect);



	if (!(zephir_instance_of_ev(dialect, phalcon_db_dialectinterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STRW(spl_ce_InvalidArgumentException, "Parameter 'dialect' must be an instance of 'Phalcon\\Db\\DialectInterface'");
		return;
	}
	zephir_update_property_this(this_ptr, SL("_dialect"), dialect TSRMLS_CC);

}

/**
 * Returns internal dialect instance
 *
 * @return Phalcon\Db\DialectInterface
 */
PHP_METHOD(Phalcon_Db_Adapter, getDialect) {


	RETURN_MEMBER(this_ptr, "_dialect");

}

/**
 * Returns the first row in a SQL query result
 *
 *<code>
 *	//Getting first robot
 *	$robot = $connection->fecthOne("SELECT * FROM robots");
 *	print_r($robot);
 *
 *	//Getting first robot with associative indexes only
 *	$robot = $connection->fecthOne("SELECT * FROM robots", Phalcon\Db::FETCH_ASSOC);
 *	print_r($robot);
 *</code>
 *
 * @param string sqlQuery
 * @param int fetchMode
 * @param array bindParams
 * @param array bindTypes
 * @return array
 */
PHP_METHOD(Phalcon_Db_Adapter, fetchOne) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *sqlQuery_param = NULL, *fetchMode = NULL, *bindParams = NULL, *bindTypes = NULL, *result = NULL;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &sqlQuery_param, &fetchMode, &bindParams, &bindTypes);

	zephir_get_strval(sqlQuery, sqlQuery_param);
	if (!fetchMode) {
		ZEPHIR_INIT_VAR(fetchMode);
		ZVAL_LONG(fetchMode, 2);
	}
	if (!bindParams) {
		bindParams = ZEPHIR_GLOBAL(global_null);
	}
	if (!bindTypes) {
		bindTypes = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_CALL_METHOD(&result, this_ptr, "query", NULL, sqlQuery, bindParams, bindTypes);
	zephir_check_call_status();
	if (Z_TYPE_P(result) == IS_OBJECT) {
		if (Z_TYPE_P(fetchMode) != IS_NULL) {
			ZEPHIR_CALL_METHOD(NULL, result, "setfetchmode", NULL, fetchMode);
			zephir_check_call_status();
		}
		ZEPHIR_RETURN_CALL_METHOD(result, "fetch", NULL);
		zephir_check_call_status();
		RETURN_MM();
	}
	array_init(return_value);
	RETURN_MM();

}

/**
 * Dumps the complete result of a query into an array
 *
 *<code>
 *	//Getting all robots with associative indexes only
 *	$robots = $connection->fetchAll("SELECT * FROM robots", Phalcon\Db::FETCH_ASSOC);
 *	foreach ($robots as $robot) {
 *		print_r($robot);
 *	}
 *
 *  //Getting all robots that contains word "robot" withing the name
 *  $robots = $connection->fetchAll("SELECT * FROM robots WHERE name LIKE :name",
 *		Phalcon\Db::FETCH_ASSOC,
 *		array('name' => '%robot%')
 *  );
 *	foreach($robots as $robot){
 *		print_r($robot);
 *	}
 *</code>
 *
 * @param string sqlQuery
 * @param int fetchMode
 * @param array bindParams
 * @param array bindTypes
 * @return array
 */
PHP_METHOD(Phalcon_Db_Adapter, fetchAll) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *sqlQuery_param = NULL, *fetchMode = NULL, *bindParams = NULL, *bindTypes = NULL, *results, *result = NULL, *row = NULL;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &sqlQuery_param, &fetchMode, &bindParams, &bindTypes);

	zephir_get_strval(sqlQuery, sqlQuery_param);
	if (!fetchMode) {
		ZEPHIR_INIT_VAR(fetchMode);
		ZVAL_LONG(fetchMode, 2);
	}
	if (!bindParams) {
		bindParams = ZEPHIR_GLOBAL(global_null);
	}
	if (!bindTypes) {
		bindTypes = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(results);
	array_init(results);
	ZEPHIR_CALL_METHOD(&result, this_ptr, "query", NULL, sqlQuery, bindParams, bindTypes);
	zephir_check_call_status();
	if (Z_TYPE_P(result) == IS_OBJECT) {
		if (Z_TYPE_P(fetchMode) != IS_NULL) {
			ZEPHIR_CALL_METHOD(NULL, result, "setfetchmode", NULL, fetchMode);
			zephir_check_call_status();
		}
		while (1) {
			ZEPHIR_CALL_METHOD(&row, result, "fetch",  NULL);
			zephir_check_call_status();
			if (!(zephir_is_true(row))) {
				break;
			} else {
				zephir_array_append(&results, row, PH_SEPARATE);
			}
		}
	}
	RETURN_CCTOR(results);

}

/**
 * Inserts data into a table using custom RBDM SQL syntax
 *
 * <code>
 * //Inserting a new robot
 * $success = $connection->insert(
 *     "robots",
 *     array("Astro Boy", 1952),
 *     array("name", "year")
 * );
 *
 * //Next SQL sentence is sent to the database system
 * INSERT INTO `robots` (`name`, `year`) VALUES ("Astro boy", 1952);
 * </code>
 *
 * @param   string|array table
 * @param 	array values
 * @param 	array fields
 * @param 	array dataTypes
 * @return 	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, insert) {

	zval *_5 = NULL;
	HashTable *_3, *_8;
	HashPosition _2, _7;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *table, *values, *fields = NULL, *dataTypes = NULL, *placeholders, *insertValues, *bindDataTypes = NULL, *bindType = NULL, *position = NULL, *value = NULL, *escapedTable = NULL, *joinedValues, *escapedFields = NULL, *field = NULL, *insertSql, *_0, *_1, **_4, *_6 = NULL, **_9, *_10 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &table, &values, &fields, &dataTypes);

	if (!fields) {
		fields = ZEPHIR_GLOBAL(global_null);
	}
	if (!dataTypes) {
		dataTypes = ZEPHIR_GLOBAL(global_null);
	}


	if (Z_TYPE_P(values) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The second parameter for insert isn't an Array");
		return;
	}
	if (!(zephir_fast_count_int(values TSRMLS_CC))) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, phalcon_db_exception_ce);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SVS(_1, "Unable to insert into ", table, " without data");
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _1);
		zephir_check_call_status();
		zephir_throw_exception(_0 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(placeholders);
	array_init(placeholders);
	ZEPHIR_INIT_VAR(insertValues);
	array_init(insertValues);
	if (Z_TYPE_P(dataTypes) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(bindDataTypes);
		array_init(bindDataTypes);
	} else {
		ZEPHIR_CPY_WRT(bindDataTypes, dataTypes);
	}
	zephir_is_iterable(values, &_3, &_2, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
	  ; zephir_hash_move_forward_ex(_3, &_2)
	) {
		ZEPHIR_GET_HMKEY(position, _3, _2);
		ZEPHIR_GET_HVALUE(value, _4);
		if (Z_TYPE_P(value) == IS_OBJECT) {
			zephir_get_strval(_5, value);
			zephir_array_append(&placeholders, _5, PH_SEPARATE);
		} else {
			if (Z_TYPE_P(value) == IS_NULL) {
				ZEPHIR_INIT_NVAR(_6);
				ZVAL_STRING(_6, "null", 1);
				zephir_array_append(&placeholders, _6, PH_SEPARATE);
			} else {
				ZEPHIR_INIT_NVAR(_6);
				ZVAL_STRING(_6, "?", 1);
				zephir_array_append(&placeholders, _6, PH_SEPARATE);
				zephir_array_append(&insertValues, value, PH_SEPARATE);
				if (Z_TYPE_P(dataTypes) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(bindType);
					if (!(zephir_array_isset_fetch(&bindType, dataTypes, position, 0 TSRMLS_CC))) {
						ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Incomplete number of bind types");
						return;
					}
					zephir_array_append(&bindDataTypes, bindType, PH_SEPARATE);
				}
			}
		}
	}
	if (ZEPHIR_GLOBAL(db).escape_identifiers) {
		ZEPHIR_CALL_METHOD(&escapedTable, this_ptr, "escapeidentifier", NULL, table);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(escapedTable, table);
	}
	ZEPHIR_INIT_VAR(joinedValues);
	zephir_fast_join_str(joinedValues, SL(", "), placeholders TSRMLS_CC);
	ZEPHIR_INIT_VAR(insertSql);
	if (Z_TYPE_P(fields) == IS_ARRAY) {
		if (ZEPHIR_GLOBAL(db).escape_identifiers) {
			ZEPHIR_INIT_VAR(escapedFields);
			array_init(escapedFields);
			zephir_is_iterable(fields, &_8, &_7, 0, 0);
			for (
			  ; zephir_hash_get_current_data_ex(_8, (void**) &_9, &_7) == SUCCESS
			  ; zephir_hash_move_forward_ex(_8, &_7)
			) {
				ZEPHIR_GET_HVALUE(field, _9);
				ZEPHIR_CALL_METHOD(&_10, this_ptr, "escapeidentifier", NULL, field);
				zephir_check_call_status();
				zephir_array_append(&escapedFields, _10, PH_SEPARATE);
			}
		} else {
			ZEPHIR_CPY_WRT(escapedFields, fields);
		}
		ZEPHIR_INIT_NVAR(_6);
		zephir_fast_join_str(_6, SL(", "), escapedFields TSRMLS_CC);
		ZEPHIR_CONCAT_SVSVSVS(insertSql, "INSERT INTO ", escapedTable, " (", _6, ") VALUES (", joinedValues, ")");
	} else {
		ZEPHIR_CONCAT_SVSVS(insertSql, "INSERT INTO ", escapedTable, " VALUES (", joinedValues, ")");
	}
	if (!(zephir_fast_count_int(bindDataTypes TSRMLS_CC))) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, insertSql, insertValues);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, insertSql, insertValues, bindDataTypes);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Updates data on a table using custom RBDM SQL syntax
 *
 * <code>
 * //Updating existing robot
 * $success = $connection->update(
 *     "robots",
 *     array("name"),
 *     array("New Astro Boy"),
 *     "id = 101"
 * );
 *
 * //Next SQL sentence is sent to the database system
 * UPDATE `robots` SET `name` = "Astro boy" WHERE id = 101
 * </code>
 *
 * @param   string|array table
 * @param 	array fields
 * @param 	array values
 * @param 	string whereCondition
 * @param 	array dataTypes
 * @return 	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, update) {

	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1;
	HashPosition _0;
	zval *table, *fields, *values, *whereCondition = NULL, *dataTypes = NULL, *placeholders, *updateValues, *position = NULL, *value = NULL, *field = NULL, *bindDataTypes = NULL, *escapedField = NULL, *bindType = NULL, *escapedTable = NULL, *setClause, *updateSql, *conditions, *whereBind, *whereTypes, **_2, *_3 = NULL, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 2, &table, &fields, &values, &whereCondition, &dataTypes);

	if (!whereCondition) {
		whereCondition = ZEPHIR_GLOBAL(global_null);
	}
	if (!dataTypes) {
		dataTypes = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(placeholders);
	array_init(placeholders);
	ZEPHIR_INIT_VAR(updateValues);
	array_init(updateValues);
	if (Z_TYPE_P(dataTypes) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(bindDataTypes);
		array_init(bindDataTypes);
	} else {
		ZEPHIR_CPY_WRT(bindDataTypes, dataTypes);
	}
	zephir_is_iterable(values, &_1, &_0, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(position, _1, _0);
		ZEPHIR_GET_HVALUE(value, _2);
		ZEPHIR_OBS_NVAR(field);
		if (!(zephir_array_isset_fetch(&field, fields, position, 0 TSRMLS_CC))) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The number of values in the update is not the same as fields");
			return;
		}
		if (ZEPHIR_GLOBAL(db).escape_identifiers) {
			ZEPHIR_CALL_METHOD(&escapedField, this_ptr, "escapeidentifier", NULL, field);
			zephir_check_call_status();
		} else {
			ZEPHIR_CPY_WRT(escapedField, field);
		}
		if (Z_TYPE_P(value) == IS_OBJECT) {
			ZEPHIR_INIT_LNVAR(_3);
			ZEPHIR_CONCAT_VSV(_3, escapedField, " = ", value);
			zephir_array_append(&placeholders, _3, PH_SEPARATE);
		} else {
			if (Z_TYPE_P(value) == IS_NULL) {
				ZEPHIR_INIT_LNVAR(_3);
				ZEPHIR_CONCAT_VS(_3, escapedField, " = null");
				zephir_array_append(&placeholders, _3, PH_SEPARATE);
			} else {
				zephir_array_append(&updateValues, value, PH_SEPARATE);
				if (Z_TYPE_P(dataTypes) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(bindType);
					if (!(zephir_array_isset_fetch(&bindType, dataTypes, position, 0 TSRMLS_CC))) {
						ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Incomplete number of bind types");
						return;
					}
					zephir_array_append(&bindDataTypes, bindType, PH_SEPARATE);
				}
				ZEPHIR_INIT_LNVAR(_4);
				ZEPHIR_CONCAT_VS(_4, escapedField, " = ?");
				zephir_array_append(&placeholders, _4, PH_SEPARATE);
			}
		}
	}
	if (ZEPHIR_GLOBAL(db).escape_identifiers) {
		ZEPHIR_CALL_METHOD(&escapedTable, this_ptr, "escapeidentifier", NULL, table);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(escapedTable, table);
	}
	ZEPHIR_INIT_VAR(setClause);
	zephir_fast_join_str(setClause, SL(", "), placeholders TSRMLS_CC);
	ZEPHIR_INIT_VAR(updateSql);
	if (Z_TYPE_P(whereCondition) != IS_NULL) {
		ZEPHIR_CONCAT_SVSVS(updateSql, "UPDATE ", escapedTable, " SET ", setClause, " WHERE ");
		if (Z_TYPE_P(whereCondition) == IS_STRING) {
			zephir_concat_self(&updateSql, whereCondition TSRMLS_CC);
		} else {
			if (Z_TYPE_P(whereCondition) != IS_ARRAY) {
				ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Invalid WHERE clause conditions");
				return;
			}
			ZEPHIR_OBS_VAR(conditions);
			if (zephir_array_isset_string_fetch(&conditions, whereCondition, SS("conditions"), 0 TSRMLS_CC)) {
				zephir_concat_self(&updateSql, conditions TSRMLS_CC);
			}
			ZEPHIR_OBS_VAR(whereBind);
			if (zephir_array_isset_string_fetch(&whereBind, whereCondition, SS("bind"), 0 TSRMLS_CC)) {
				ZEPHIR_CALL_FUNCTION(NULL, "merge_append", &_5, updateValues, whereBind);
				zephir_check_call_status();
			}
			ZEPHIR_OBS_VAR(whereTypes);
			if (zephir_array_isset_string_fetch(&whereTypes, whereCondition, SS("bindTypes"), 0 TSRMLS_CC)) {
				ZEPHIR_CALL_FUNCTION(NULL, "merge_append", &_5, bindDataTypes, whereTypes);
				zephir_check_call_status();
			}
		}
	} else {
		ZEPHIR_CONCAT_SVSV(updateSql, "UPDATE ", escapedTable, " SET ", setClause);
	}
	if (!(zephir_fast_count_int(bindDataTypes TSRMLS_CC))) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, updateSql, updateValues);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, updateSql, updateValues, bindDataTypes);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Deletes data from a table using custom RBDM SQL syntax
 *
 * <code>
 * //Deleting existing robot
 * $success = $connection->delete(
 *     "robots",
 *     "id = 101"
 * );
 *
 * //Next SQL sentence is generated
 * DELETE FROM `robots` WHERE `id` = 101
 * </code>
 *
 * @param  string|array table
 * @param  string whereCondition
 * @param  array placeholders
 * @param  array dataTypes
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, delete) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *table, *whereCondition = NULL, *placeholders = NULL, *dataTypes = NULL, *sql, *escapedTable = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &table, &whereCondition, &placeholders, &dataTypes);

	if (!whereCondition) {
		whereCondition = ZEPHIR_GLOBAL(global_null);
	}
	if (!placeholders) {
		placeholders = ZEPHIR_GLOBAL(global_null);
	}
	if (!dataTypes) {
		dataTypes = ZEPHIR_GLOBAL(global_null);
	}


	if (ZEPHIR_GLOBAL(db).escape_identifiers) {
		ZEPHIR_CALL_METHOD(&escapedTable, this_ptr, "escapeidentifier", NULL, table);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(escapedTable, table);
	}
	ZEPHIR_INIT_VAR(sql);
	if (!(ZEPHIR_IS_EMPTY(whereCondition))) {
		ZEPHIR_CONCAT_SVSV(sql, "DELETE FROM ", escapedTable, " WHERE ", whereCondition);
	} else {
		ZEPHIR_CONCAT_SV(sql, "DELETE FROM ", escapedTable);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, sql, placeholders, dataTypes);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Gets a list of columns
 *
 * @param	array columnList
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Adapter, getColumnList) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *columnList, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &columnList);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "getcolumnlist", NULL, columnList);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Appends a LIMIT clause to $sqlQuery argument
 *
 * <code>
 * 	echo $connection->limit("SELECT * FROM robots", 5);
 * </code>
 *
 * @param  	string sqlQuery
 * @param 	int number
 * @return 	string
 */
PHP_METHOD(Phalcon_Db_Adapter, limit) {

	int number, ZEPHIR_LAST_CALL_STATUS;
	zval *sqlQuery_param = NULL, *number_param = NULL, *_0, *_1;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &sqlQuery_param, &number_param);

	if (Z_TYPE_P(sqlQuery_param) != IS_STRING && Z_TYPE_P(sqlQuery_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlQuery' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(sqlQuery_param) == IS_STRING) {
		sqlQuery = sqlQuery_param;
	} else {
		ZEPHIR_INIT_VAR(sqlQuery);
		ZVAL_EMPTY_STRING(sqlQuery);
	}
	number = zephir_get_intval(number_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, number);
	ZEPHIR_RETURN_CALL_METHOD(_0, "limit", NULL, sqlQuery, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generates SQL checking for the existence of a schema.table
 *
 * <code>
 * 	var_dump($connection->tableExists("blog", "posts"));
 * </code>
 *
 * @param string tableName
 * @param string schemaName
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, tableExists) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3, *_4;
	zval *tableName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &tableName_param, &schemaName_param);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (!schemaName_param) {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	} else {
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}
	}


	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "tableexists", NULL, tableName, schemaName);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchone", NULL, _2, _3);
	zephir_check_call_status();
	zephir_array_fetch_long(&_4, _0, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
	RETURN_MM_BOOL(ZEPHIR_GT_LONG(_4, 0));

}

/**
 * Generates SQL checking for the existence of a schema.view
 *
 *<code>
 * var_dump($connection->viewExists("active_users", "posts"));
 *</code>
 *
 * @param string viewName
 * @param string schemaName
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, viewExists) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *viewName_param = NULL, *schemaName = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3, *_4;
	zval *viewName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &viewName_param, &schemaName);

	if (Z_TYPE_P(viewName_param) != IS_STRING && Z_TYPE_P(viewName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'viewName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(viewName_param) == IS_STRING) {
		viewName = viewName_param;
	} else {
		ZEPHIR_INIT_VAR(viewName);
		ZVAL_EMPTY_STRING(viewName);
	}
	if (!schemaName) {
		schemaName = ZEPHIR_GLOBAL(global_null);
	}


	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "viewexists", NULL, viewName, schemaName);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchone", NULL, _2, _3);
	zephir_check_call_status();
	zephir_array_fetch_long(&_4, _0, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
	RETURN_MM_BOOL(ZEPHIR_GT_LONG(_4, 0));

}

/**
 * Returns a SQL modified with a FOR UPDATE clause
 *
 * @param	string sqlQuery
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Adapter, forUpdate) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *sqlQuery_param = NULL, *_0;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sqlQuery_param);

	if (Z_TYPE_P(sqlQuery_param) != IS_STRING && Z_TYPE_P(sqlQuery_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlQuery' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(sqlQuery_param) == IS_STRING) {
		sqlQuery = sqlQuery_param;
	} else {
		ZEPHIR_INIT_VAR(sqlQuery);
		ZVAL_EMPTY_STRING(sqlQuery);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "forupdate", NULL, sqlQuery);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns a SQL modified with a LOCK IN SHARE MODE clause
 *
 * @param	string sqlQuery
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Adapter, sharedLock) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *sqlQuery_param = NULL, *_0;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sqlQuery_param);

	if (Z_TYPE_P(sqlQuery_param) != IS_STRING && Z_TYPE_P(sqlQuery_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlQuery' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(sqlQuery_param) == IS_STRING) {
		sqlQuery = sqlQuery_param;
	} else {
		ZEPHIR_INIT_VAR(sqlQuery);
		ZVAL_EMPTY_STRING(sqlQuery);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "sharedlock", NULL, sqlQuery);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Creates a table
 *
 * @param	string tableName
 * @param	string schemaName
 * @param	array definition
 * @return	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, createTable) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *definition, *columns, *_0, *_2, *_3 = NULL;
	zval *tableName = NULL, *schemaName = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tableName_param, &schemaName_param, &definition);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}


	if (Z_TYPE_P(definition) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, phalcon_db_exception_ce);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SVS(_1, "Invalid definition to create the table '", tableName, "'");
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _1);
		zephir_check_call_status();
		zephir_throw_exception(_0 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_OBS_VAR(columns);
	if (!(zephir_array_isset_string_fetch(&columns, definition, SS("columns"), 0 TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The table must contain at least one column");
		return;
	}
	if (!(zephir_fast_count_int(columns TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The table must contain at least one column");
		return;
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_3, _2, "createtable", NULL, tableName, schemaName, definition);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Drops a table from a schema/database
 *
 * @param	string tableName
 * @param   string schemaName
 * @param	boolean ifExists
 * @return	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, dropTable) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *ifExists = NULL, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &tableName_param, &schemaName_param, &ifExists);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (!schemaName_param) {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	} else {
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}
	}
	if (!ifExists) {
		ifExists = ZEPHIR_GLOBAL(global_true);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "droptable", NULL, tableName, schemaName, ifExists);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Creates a view
 *
 * @param	string tableName
 * @param	array definition
 * @param	string schemaName
 * @return	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, createView) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *viewName_param = NULL, *definition, *schemaName = NULL, *_0, *_2, *_3 = NULL;
	zval *viewName = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &viewName_param, &definition, &schemaName);

	if (Z_TYPE_P(viewName_param) != IS_STRING && Z_TYPE_P(viewName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'viewName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(viewName_param) == IS_STRING) {
		viewName = viewName_param;
	} else {
		ZEPHIR_INIT_VAR(viewName);
		ZVAL_EMPTY_STRING(viewName);
	}
	if (!schemaName) {
		schemaName = ZEPHIR_GLOBAL(global_null);
	}


	if (Z_TYPE_P(definition) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, phalcon_db_exception_ce);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SVS(_1, "Invalid definition to create the view '", viewName, "'");
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _1);
		zephir_check_call_status();
		zephir_throw_exception(_0 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (!(zephir_array_isset_string(definition, SS("sql")))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The table must contain at least one column");
		return;
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_3, _2, "createview", NULL, viewName, definition, schemaName);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Drops a view
 *
 * @param	string viewName
 * @param   string schemaName
 * @param	boolean ifExists
 * @return	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, dropView) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *viewName_param = NULL, *schemaName_param = NULL, *ifExists = NULL, *_0, *_1 = NULL;
	zval *viewName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &viewName_param, &schemaName_param, &ifExists);

	if (Z_TYPE_P(viewName_param) != IS_STRING && Z_TYPE_P(viewName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'viewName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(viewName_param) == IS_STRING) {
		viewName = viewName_param;
	} else {
		ZEPHIR_INIT_VAR(viewName);
		ZVAL_EMPTY_STRING(viewName);
	}
	if (!schemaName_param) {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	} else {
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}
	}
	if (!ifExists) {
		ifExists = ZEPHIR_GLOBAL(global_true);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "dropview", NULL, viewName, schemaName, ifExists);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Adds a column to a table
 *
 * @param	string tableName
 * @param 	string schemaName
 * @param	Phalcon\Db\ColumnInterface column
 * @return	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, addColumn) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *column, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tableName_param, &schemaName_param, &column);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}


	if (!(zephir_instance_of_ev(column, phalcon_db_columninterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'column' must be an instance of 'Phalcon\\Db\\ColumnInterface'");
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "addcolumn", NULL, tableName, schemaName, column);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Modifies a table column based on a definition
 *
 * @param	string tableName
 * @param	string schemaName
 * @param	Phalcon\Db\ColumnInterface column
 * @return 	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, modifyColumn) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *column, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tableName_param, &schemaName_param, &column);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}


	if (!(zephir_instance_of_ev(column, phalcon_db_columninterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'column' must be an instance of 'Phalcon\\Db\\ColumnInterface'");
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "modifycolumn", NULL, tableName, schemaName, column);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Drops a column from a table
 *
 * @param	string tableName
 * @param	string schemaName
 * @param	string columnName
 * @return 	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, dropColumn) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *columnName_param = NULL, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL, *columnName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tableName_param, &schemaName_param, &columnName_param);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}
	zephir_get_strval(columnName, columnName_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "dropcolumn", NULL, tableName, schemaName, columnName);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Adds an index to a table
 *
 * @param	string tableName
 * @param	string schemaName
 * @param	Phalcon\Db\IndexInterface index
 * @return 	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, addIndex) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *index, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tableName_param, &schemaName_param, &index);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}


	if (!(zephir_instance_of_ev(index, phalcon_db_indexinterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'index' must be an instance of 'Phalcon\\Db\\IndexInterface'");
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "addindex", NULL, tableName, schemaName, index);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Drop an index from a table
 *
 * @param	string tableName
 * @param	string schemaName
 * @param	string indexName
 * @return 	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, dropIndex) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *indexName, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tableName_param, &schemaName_param, &indexName);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "dropindex", NULL, tableName, schemaName, indexName);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Adds a primary key to a table
 *
 * @param	string tableName
 * @param	string schemaName
 * @param	Phalcon\Db\IndexInterface index
 * @return 	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, addPrimaryKey) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *index, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tableName_param, &schemaName_param, &index);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}


	if (!(zephir_instance_of_ev(index, phalcon_db_indexinterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'index' must be an instance of 'Phalcon\\Db\\IndexInterface'");
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "addprimarykey", NULL, tableName, schemaName, index);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Drops a table's primary key
 *
 * @param	string tableName
 * @param	string schemaName
 * @return 	boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, dropPrimaryKey) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &tableName_param, &schemaName_param);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "dropprimarykey", NULL, tableName, schemaName);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Adds a foreign key to a table
 *
 * @param	string tableName
 * @param	string schemaName
 * @param	Phalcon\Db\ReferenceInterface reference
 * @return	boolean true
 */
PHP_METHOD(Phalcon_Db_Adapter, addForeignKey) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *reference, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tableName_param, &schemaName_param, &reference);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}


	if (!(zephir_instance_of_ev(reference, phalcon_db_referenceinterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'reference' must be an instance of 'Phalcon\\Db\\ReferenceInterface'");
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "addforeignkey", NULL, tableName, schemaName, reference);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Drops a foreign key from a table
 *
 * @param	string tableName
 * @param	string schemaName
 * @param	string referenceName
 * @return	boolean true
 */
PHP_METHOD(Phalcon_Db_Adapter, dropForeignKey) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName_param = NULL, *schemaName_param = NULL, *referenceName_param = NULL, *_0, *_1 = NULL;
	zval *tableName = NULL, *schemaName = NULL, *referenceName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tableName_param, &schemaName_param, &referenceName_param);

	if (Z_TYPE_P(tableName_param) != IS_STRING && Z_TYPE_P(tableName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tableName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(tableName_param) == IS_STRING) {
		tableName = tableName_param;
	} else {
		ZEPHIR_INIT_VAR(tableName);
		ZVAL_EMPTY_STRING(tableName);
	}
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}
	if (Z_TYPE_P(referenceName_param) != IS_STRING && Z_TYPE_P(referenceName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'referenceName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(referenceName_param) == IS_STRING) {
		referenceName = referenceName_param;
	} else {
		ZEPHIR_INIT_VAR(referenceName);
		ZVAL_EMPTY_STRING(referenceName);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "dropforeignkey", NULL, tableName, schemaName, referenceName);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the SQL column definition from a column
 *
 * @param	Phalcon\Db\ColumnInterface column
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Adapter, getColumnDefinition) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *column, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &column);



	if (!(zephir_instance_of_ev(column, phalcon_db_columninterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'column' must be an instance of 'Phalcon\\Db\\ColumnInterface'");
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "getcolumndefinition", NULL, column);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * List all tables on a database
 *
 *<code>
 * 	print_r($connection->listTables("blog"));
 *</code>
 *
 * @param string schemaName
 * @return array
 */
PHP_METHOD(Phalcon_Db_Adapter, listTables) {

	HashTable *_5;
	HashPosition _4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *schemaName_param = NULL, *table = NULL, *allTables, *_0 = NULL, *_1, *_2 = NULL, *_3, **_6, *_7;
	zval *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &schemaName_param);

	if (!schemaName_param) {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	} else {
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}
	}


	ZEPHIR_INIT_VAR(allTables);
	array_init(allTables);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "listtables", NULL, schemaName);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchall", NULL, _2, _3);
	zephir_check_call_status();
	zephir_is_iterable(_0, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HVALUE(table, _6);
		zephir_array_fetch_long(&_7, table, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_array_append(&allTables, _7, PH_SEPARATE);
	}
	RETURN_CCTOR(allTables);

}

/**
 * List all views on a database
 *
 *<code>
 *	print_r($connection->listViews("blog"));
 *</code>
 *
 * @param string schemaName
 * @return array
 */
PHP_METHOD(Phalcon_Db_Adapter, listViews) {

	HashTable *_5;
	HashPosition _4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *schemaName_param = NULL, *table = NULL, *allTables, *_0 = NULL, *_1, *_2 = NULL, *_3, **_6, *_7;
	zval *schemaName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &schemaName_param);

	if (!schemaName_param) {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	} else {
	if (Z_TYPE_P(schemaName_param) != IS_STRING && Z_TYPE_P(schemaName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schemaName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schemaName_param) == IS_STRING) {
		schemaName = schemaName_param;
	} else {
		ZEPHIR_INIT_VAR(schemaName);
		ZVAL_EMPTY_STRING(schemaName);
	}
	}


	ZEPHIR_INIT_VAR(allTables);
	array_init(allTables);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "listviews", NULL, schemaName);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchall", NULL, _2, _3);
	zephir_check_call_status();
	zephir_is_iterable(_0, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HVALUE(table, _6);
		zephir_array_fetch_long(&_7, table, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_array_append(&allTables, _7, PH_SEPARATE);
	}
	RETURN_CCTOR(allTables);

}

/**
 * Lists table indexes
 *
 *<code>
 *	print_r($connection->describeIndexes('robots_parts'));
 *</code>
 *
 * @param	string table
 * @param	string schema
 * @return	Phalcon\Db\Index[]
 */
PHP_METHOD(Phalcon_Db_Adapter, describeIndexes) {

	zephir_fcall_cache_entry *_11 = NULL;
	HashTable *_5, *_8;
	HashPosition _4, _7;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *table_param = NULL, *schema = NULL, *indexes, *index = NULL, *keyName, *indexObjects, *name = NULL, *indexColumns = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3 = NULL, **_6, **_9, *_10 = NULL;
	zval *table = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &table_param, &schema);

	if (Z_TYPE_P(table_param) != IS_STRING && Z_TYPE_P(table_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'table' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(table_param) == IS_STRING) {
		table = table_param;
	} else {
		ZEPHIR_INIT_VAR(table);
		ZVAL_EMPTY_STRING(table);
	}
	if (!schema) {
		schema = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(indexes);
	array_init(indexes);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "describeindexes", NULL, table, schema);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchall", NULL, _2, _3);
	zephir_check_call_status();
	zephir_is_iterable(_0, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HVALUE(index, _6);
		zephir_array_fetch_long(&keyName, index, 2, PH_NOISY | PH_READONLY TSRMLS_CC);
		if (!(zephir_array_isset(indexes, keyName))) {
			ZEPHIR_INIT_NVAR(_3);
			array_init(_3);
			zephir_array_update_zval(&indexes, keyName, &_3, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_VAR(indexObjects);
	array_init(indexObjects);
	zephir_is_iterable(indexes, &_8, &_7, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_8, (void**) &_9, &_7) == SUCCESS
	  ; zephir_hash_move_forward_ex(_8, &_7)
	) {
		ZEPHIR_GET_HMKEY(name, _8, _7);
		ZEPHIR_GET_HVALUE(indexColumns, _9);
		ZEPHIR_INIT_LNVAR(_10);
		object_init_ex(_10, phalcon_db_index_ce);
		ZEPHIR_CALL_METHOD(NULL, _10, "__construct", &_11, name, indexColumns);
		zephir_check_call_status();
		zephir_array_update_zval(&indexObjects, name, &_10, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(indexObjects);

}

/**
 * Lists table references
 *
 *<code>
 * print_r($connection->describeReferences('robots_parts'));
 *</code>
 *
 * @param	string table
 * @param	string schema
 * @return	Phalcon\Db\Reference[]
 */
PHP_METHOD(Phalcon_Db_Adapter, describeReferences) {

	zephir_fcall_cache_entry *_13 = NULL;
	zval *_7 = NULL;
	HashTable *_5, *_10;
	HashPosition _4, _9;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *table_param = NULL, *schema_param = NULL, *emptyArr, *references, *reference = NULL, *arrayReference = NULL, *constraintName, *referenceObjects, *name = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3, **_6, *_8 = NULL, **_11, *_12 = NULL;
	zval *table = NULL, *schema = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &table_param, &schema_param);

	if (Z_TYPE_P(table_param) != IS_STRING && Z_TYPE_P(table_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'table' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(table_param) == IS_STRING) {
		table = table_param;
	} else {
		ZEPHIR_INIT_VAR(table);
		ZVAL_EMPTY_STRING(table);
	}
	if (!schema_param) {
		ZEPHIR_INIT_VAR(schema);
		ZVAL_EMPTY_STRING(schema);
	} else {
	if (Z_TYPE_P(schema_param) != IS_STRING && Z_TYPE_P(schema_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'schema' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(schema_param) == IS_STRING) {
		schema = schema_param;
	} else {
		ZEPHIR_INIT_VAR(schema);
		ZVAL_EMPTY_STRING(schema);
	}
	}


	ZEPHIR_INIT_VAR(emptyArr);
	array_init(emptyArr);
	ZEPHIR_INIT_VAR(references);
	array_init(references);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "describereferences", NULL, table, schema);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 3);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "fetchall", NULL, _2, _3);
	zephir_check_call_status();
	zephir_is_iterable(_0, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HVALUE(reference, _6);
		zephir_array_fetch_long(&constraintName, reference, 2, PH_NOISY | PH_READONLY TSRMLS_CC);
		if (!(zephir_array_isset(references, constraintName))) {
			ZEPHIR_INIT_NVAR(_7);
			array_init_size(_7, 7);
			ZEPHIR_OBS_NVAR(_8);
			zephir_array_fetch_long(&_8, reference, 3, PH_NOISY TSRMLS_CC);
			zephir_array_update_string(&_7, SL("referencedSchema"), &_8, PH_COPY | PH_SEPARATE);
			ZEPHIR_OBS_NVAR(_8);
			zephir_array_fetch_long(&_8, reference, 4, PH_NOISY TSRMLS_CC);
			zephir_array_update_string(&_7, SL("referencedTable"), &_8, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_7, SL("columns"), &emptyArr, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&_7, SL("referencedColumns"), &emptyArr, PH_COPY | PH_SEPARATE);
			zephir_array_update_zval(&references, constraintName, &_7, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_VAR(referenceObjects);
	array_init(referenceObjects);
	zephir_is_iterable(references, &_10, &_9, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
	  ; zephir_hash_move_forward_ex(_10, &_9)
	) {
		ZEPHIR_GET_HMKEY(name, _10, _9);
		ZEPHIR_GET_HVALUE(arrayReference, _11);
		ZEPHIR_INIT_LNVAR(_12);
		object_init_ex(_12, phalcon_db_reference_ce);
		ZEPHIR_INIT_NVAR(_7);
		array_init_size(_7, 7);
		ZEPHIR_OBS_NVAR(_8);
		zephir_array_fetch_string(&_8, arrayReference, SL("referencedSchema"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&_7, SL("referencedSchema"), &_8, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_8);
		zephir_array_fetch_string(&_8, arrayReference, SL("referencedTable"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&_7, SL("referencedTable"), &_8, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_8);
		zephir_array_fetch_string(&_8, arrayReference, SL("columns"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&_7, SL("columns"), &_8, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_8);
		zephir_array_fetch_string(&_8, arrayReference, SL("referencedColumns"), PH_NOISY TSRMLS_CC);
		zephir_array_update_string(&_7, SL("referencedColumns"), &_8, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(NULL, _12, "__construct", &_13, name, _7);
		zephir_check_call_status();
		zephir_array_update_zval(&referenceObjects, name, &_12, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(referenceObjects);

}

/**
 * Gets creation options from a table
 *
 *<code>
 * print_r($connection->tableOptions('robots'));
 *</code>
 *
 * @param	string tableName
 * @param	string schemaName
 * @return	array
 */
PHP_METHOD(Phalcon_Db_Adapter, tableOptions) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tableName, *schemaName = NULL, *sql = NULL, *_0, *_1 = NULL, *_2, *_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &tableName, &schemaName);

	if (!schemaName) {
		schemaName = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&sql, _0, "tableoptions", NULL, tableName, schemaName);
	zephir_check_call_status();
	if (zephir_is_true(sql)) {
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, 3);
		ZEPHIR_CALL_METHOD(&_1, this_ptr, "fetchall", NULL, sql, _2);
		zephir_check_call_status();
		zephir_array_fetch_long(&_3, _1, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		RETURN_CTOR(_3);
	}
	array_init(return_value);
	RETURN_MM();

}

/**
 * Creates a new savepoint
 *
 * @param string name
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, createSavepoint) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *dialect, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(name_param) == IS_STRING) {
		name = name_param;
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_OBS_VAR(dialect);
	zephir_read_property_this(&dialect, this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_0, dialect, "supportssavepoints",  NULL);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Savepoints are not supported by this database adapter.");
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, dialect, "createsavepoint", NULL, name);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Releases given savepoint
 *
 * @param string name
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, releaseSavepoint) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *dialect, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(name_param) == IS_STRING) {
		name = name_param;
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_OBS_VAR(dialect);
	zephir_read_property_this(&dialect, this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_0, dialect, "supportssavepoints",  NULL);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Savepoints are not supported by this database adapter");
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, dialect, "supportsreleasesavepoints",  NULL);
	zephir_check_call_status();
	if (zephir_is_true(_0)) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&_0, dialect, "releasesavepoint", NULL, name);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Rollbacks given savepoint
 *
 * @param string name
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, rollbackSavepoint) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *dialect, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(name_param) == IS_STRING) {
		name = name_param;
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_OBS_VAR(dialect);
	zephir_read_property_this(&dialect, this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_0, dialect, "supportssavepoints",  NULL);
	zephir_check_call_status();
	if (!(zephir_is_true(_0))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Savepoints are not supported by this database adapter");
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, dialect, "rollbacksavepoint", NULL, name);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "execute", NULL, _0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Set if nested transactions should use savepoints
 *
 * @param boolean nestedTransactionsWithSavepoints
 * @return Phalcon\Db\AdapterInterface
 */
PHP_METHOD(Phalcon_Db_Adapter, setNestedTransactionsWithSavepoints) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *nestedTransactionsWithSavepoints_param = NULL, *_0, *_1, *_2 = NULL;
	zend_bool nestedTransactionsWithSavepoints;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &nestedTransactionsWithSavepoints_param);

	nestedTransactionsWithSavepoints = zephir_get_boolval(nestedTransactionsWithSavepoints_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_transactionLevel"), PH_NOISY_CC);
	if (ZEPHIR_GT_LONG(_0, 0)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Nested transaction with savepoints behavior cannot be changed while a transaction is open");
		return;
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_dialect"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "supportssavepoints",  NULL);
	zephir_check_call_status();
	if (!(zephir_is_true(_2))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Savepoints are not supported by this database adapter");
		return;
	}
	zephir_update_property_this(this_ptr, SL("_transactionsWithSavepoints"), nestedTransactionsWithSavepoints ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Returns if nested transactions should use savepoints
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, isNestedTransactionsWithSavepoints) {


	RETURN_MEMBER(this_ptr, "_transactionsWithSavepoints");

}

/**
 * Returns the savepoint name to use for nested transactions
 *
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter, getNestedTransactionSavepointName) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_transactionLevel"), PH_NOISY_CC);
	ZEPHIR_CONCAT_SV(return_value, "PHALCON_SAVEPOINT_", _0);
	return;

}

/**
 * Returns the default identity value to be inserted in an identity column
 *
 *<code>
 * //Inserting a new robot with a valid default value for the column 'id'
 * $success = $connection->insert(
 *     "robots",
 *     array($connection->getDefaultIdValue(), "Astro Boy", 1952),
 *     array("id", "name", "year")
 * );
 *</code>
 *
 * @return Phalcon\Db\RawValue
 */
PHP_METHOD(Phalcon_Db_Adapter, getDefaultIdValue) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, phalcon_db_rawvalue_ce);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "null", 0);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Check whether the database system requires a sequence to produce auto-numeric values
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, supportSequences) {


	RETURN_BOOL(0);

}

/**
 * Check whether the database system requires an explicit value for identity columns
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter, useExplicitIdValue) {


	RETURN_BOOL(0);

}

/**
 * Return descriptor used to connect to the active database
 *
 * @return array
 */
PHP_METHOD(Phalcon_Db_Adapter, getDescriptor) {


	RETURN_MEMBER(this_ptr, "_descriptor");

}

/**
 * Gets the active connection unique identifier
 *
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter, getConnectionId) {


	RETURN_MEMBER(this_ptr, "_connectionId");

}

/**
 * Active SQL statement in the object
 *
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter, getSQLStatement) {


	RETURN_MEMBER(this_ptr, "_sqlStatement");

}

/**
 * Active SQL statement in the object without replace bound paramters
 *
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter, getRealSQLStatement) {


	RETURN_MEMBER(this_ptr, "_sqlStatement");

}

/**
 * Active SQL statement in the object
 *
 * @return array
 */
PHP_METHOD(Phalcon_Db_Adapter, getSQLBindTypes) {


	RETURN_MEMBER(this_ptr, "_sqlBindTypes");

}

