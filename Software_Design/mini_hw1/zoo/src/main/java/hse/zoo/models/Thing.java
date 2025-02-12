package hse.zoo.models;

import hse.zoo.interfaces.IInventory;

public class Thing implements IInventory {
    private String type;
    private int inventory_number;

    public Thing(String type, int number) {
        this.type = type;
        this.inventory_number = number;
    }

    @Override
    public int GetInventoryNumber() {
        return inventory_number;
    }

    public String GetType() {
        return type;
    }
}
