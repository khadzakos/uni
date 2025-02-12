package hse.zoo.models;

public class Herbo extends Animal {
    private final int kindness;

    public Herbo(String name, String type, int food, boolean is_healthy, int kindness) {
        super(name, type, "Herbo", food, is_healthy);
        this.kindness = kindness;
    }

    public boolean IsKind() {
        return kindness > 5;
    }
}
