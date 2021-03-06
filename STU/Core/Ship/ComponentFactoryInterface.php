<?hh // strict
namespace STU\Core\Ship;

use STU\Model\ShipTableInterface;

interface ComponentFactoryInterface {

	public function createLongRangeScanner(ShipTableInterface $ship): LongRangeScannerInterface;

	public function createShortRangeScanner(ShipTableInterface $ship): ShortRangeScannerInterface;

	public function createMove(ShipTableInterface $ship): MoveInterface;
}
