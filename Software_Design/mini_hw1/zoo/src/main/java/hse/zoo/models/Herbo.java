package hse.zoo.models;

public class Herbo extends Animal {
    private final int kindness;

    public Herbo(String name, String type, int food, int number, boolean is_healthy, int kindness) {
        super(name, type, "Herbo", food, number, is_healthy);
        this.kindness = kindness;
    }

    public boolean IsKind() {
        return kindness > 5;
    }
}
