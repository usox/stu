<?hh // strict
namespace STU\Core\Type;

use STU\Model\ShipTableInterface;

final class Ship implements \JsonSerializable {

	public function __construct(private ShipTableInterface $ship): void {
	}
	
	public function jsonSerialize(): array<string, mixed> {
		return [
			'id' => $this->ship->getId(),
			'name' => $this->ship->getName(),
			'hull' => $this->ship->getHull(),
			'type_id' => 1,
			'cx' => $this->ship->getCx(),
			'cy' => $this->ship->getCy(),
			'energy' => $this->ship->getEnergy(),
			'shield' => $this->ship->getShields(),
			'shield_active' => $this->ship->getShieldActive(),
			'lrs_active' => $this->ship->getLrsActive(),
			'srs_active' => $this->ship->getSrsActive()
		];
	}
}
