<?hh
use Monolog\Handler\StreamHandler;
use Monolog\Logger;

$di_container = new \STU\DI\DIContainer();

$di_container['database'] = function($c): Usox\HaDb\DatabaseInterface {
	return new Usox\HaDb\DatabasePostgres(new STU\Database\Configuration());
};
$di_container['session_storage'] = function($c): STU\Session\Storage {
	return new STU\Session\Storage();
};
$di_container['session_manager'] = function ($c): STU\Session\Manager {
	return new STU\Session\Manager($c);
};

$di_container['logger'] = function($c): Logger {
	$log_handler = new Logger('stu75');
	$log_handler->pushHandler(new StreamHandler('/var/www/stu75/log/app.log', Logger::DEBUG));	

	return $log_handler;
};

$di_container['ship_component_factory'] = function ($c): STU\Core\Ship\ComponentFactoryInterface {
	return new STU\Core\Ship\ComponentFactory();
};

$di_container['map_component_factory'] = function ($c): STU\Core\Map\ComponentFactoryInterface {
	return new STU\Core\Map\ComponentFactory($c->map);
};

/**
$di_container['planet_component_factory'] = function ($c): STU\Core\Planet\ComponentFactoryInterface {
	return new STU\Core\Planet\ComponentFactory($c->map);
};
 */

$di_container['core_rpc_handler_planet_handler_factory'] = function ($c): STU\Core\RPC\Handler\PlanetHandlerFactory {
	return new STU\Core\RPC\Handler\PlanetHandlerFactory($c->planet_table);
};

// Model

$di_container['user'] = $di_container->factory(function ($c): STU\Model\UserTableInterface {
	return new STU\Model\UserTable($c['database']);
});
$di_container['ship'] = $di_container->factory(function ($c): STU\Model\ShipTableInterface {
	return new STU\Model\ShipTable($c['database']);
});
$di_container['map'] = $di_container->factory(function ($c): STU\Model\MapTableInterface {
	return new STU\Model\MapTable($c['database']);
});
$di_container['planet_table'] = $di_container->factory(function ($c): STU\Model\PlanetTableInterface {
	return new STU\Model\PlanetTable($c['database']);
});
$di_container['ship_storage'] = $di_container->factory(function ($c): STU\Model\ShipStorageTableInterface {
	return new STU\Model\ShipStorageTable($c['database']);
});
