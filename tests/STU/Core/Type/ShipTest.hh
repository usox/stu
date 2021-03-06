<?hh
namespace STU\Core\Type;

use STU\Model\ShipTableInterface;
use Mockery as m;

class ShipTest extends \PHPUnit_Framework_TestCase {

	public function setUp() {
		$this->ship = m::mock(ShipTableInterface::class);

		$this->type = new Ship($this->ship);
	}

	public function testJsonSerializeReturnsCorrectDict() {
		$id = 42;
		$name = 'my-fancy-ship';
		$hull_points = 123;
		$type_id = 1;
		$cx = 666;
		$cy = 999;
		$energy = 111;
		$shield_points = 222;
		$shield_active = 1;
		$lrs_active = 1;
		$srs_active = 1;

		$this->ship->shouldReceive('getId')->once()->andReturn($id);
		$this->ship->shouldReceive('getName')->once()->andReturn($name);
		$this->ship->shouldReceive('getHull')->once()->andReturn($hull_points);
		$this->ship->shouldReceive('getCx')->once()->andReturn($cx);
		$this->ship->shouldReceive('getCy')->once()->andReturn($cy);
		$this->ship->shouldReceive('getEnergy')->once()->andReturn($energy);
		$this->ship->shouldReceive('getShields')->once()->andReturn($shield_points);
		$this->ship->shouldReceive('getShieldActive')->once()->andReturn($shield_active);
		$this->ship->shouldReceive('getLrsActive')->once()->andReturn($lrs_active);
		$this->ship->shouldReceive('getSrsActive')->once()->andReturn($srs_active);
		
		$this->assertSame(
			[
				'id' => $id,
				'name' => $name,
				'hull' => $hull_points,
				'type_id' => $type_id,
				'cx' => $cx,
				'cy' => $cy,
				'energy' => $energy,
				'shield' => $shield_points,
				'shield_active' => $shield_active,
				'lrs_active' => $lrs_active,
				'srs_active' => $srs_active
			],
			$this->type->jsonSerialize()
		);
	}
}
