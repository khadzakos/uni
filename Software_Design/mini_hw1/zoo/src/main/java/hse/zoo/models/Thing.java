package hse.zoo.models;

import hse.zoo.interfaces.IInventory;

public class Thing implements IInventory {
    private int inventory_number;

    public Thing(int number) {
        this.inventory_number = number;
    }

    @Override
    public int GetInventoryNumber() {
        return inventory_number;
    }

    public void SetInventoryNumber(int inventory_number) {
        this.inventory_number = inventory_number;
    }
}
