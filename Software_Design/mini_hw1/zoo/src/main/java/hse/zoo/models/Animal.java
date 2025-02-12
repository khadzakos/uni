package hse.zoo.models;

import hse.zoo.interfaces.IAlive;
import hse.zoo.interfaces.IInventory;

public class Animal implements IAlive, IInventory {
    private final String name;
    private final String type;
    private final String classification;
    private final int food;
    private final int inventory_number;
    private boolean is_healthy;

    public Animal(String name, String type, String classification, int food, int number, boolean is_healthy) {
        this.name = name;
        this.type = type;
        this.classification = classification;
        this.food = food;
        this.inventory_number = number;
        this.is_healthy = is_healthy;
    }

    @Override
    public int GetFoodFactor() {
        return food;
    }

    @Override
    public int GetInventoryNumber() {
        return inventory_number;
    }

    public String GetName() {
        return name;
    }

    public String GetType() {
        return type;
    }

    public String GetClassification() {
        return classification;
    }

    public boolean IsHealthy() {
        return is_healthy;
    }

}
