package hse.zoo.services;

import hse.zoo.models.*;

import java.util.ArrayList;
import java.util.List;

public class Zoo {
    private VetClinic clinic;
    private int inventory_number = 0;
    private final List<Animal> animals = new ArrayList<>();
    private final List<Thing> inventory = new ArrayList<>();

    public Zoo(VetClinic clinic) {
        this.clinic = clinic;
    }

    public void AddAnimal(Animal animal) {
        if (clinic.IsHealthy(animal)) {
            animal.SetInventoryNumber(inventory_number);
            animals.add(animal);
            inventory_number++;
            System.out.println(animal.GetType() + " " + animal.GetName() + " принят в зоопарк.");
        } else {
            System.out.println("К сожалению, " + animal.GetType() + " " + animal.GetName() + " не прошел проверку ветеринара и не может быть добавлен в зоопарк.");
        }
    }

    public void AddThing(Thing thing) {
        thing.SetInventoryNumber(inventory_number);
        inventory.add(thing);
        inventory_number++;
        System.out.println("Предмет " + thing.GetInventoryNumber() + " добавлен в инвентарь.");
    }

    public void ShowAnimals() {
        System.out.println("Животные в зоопарке:");
        for (Animal animal : animals) {
            System.out.println(animal.GetType() + " " + animal.GetName() + " - " + (animal.GetClassification().equals("Herbo") ? "Травоядное" : "Плотоядное"));
        }
    }

    public void ShowContactAnimals() {
        System.out.println("Животные в зоопарке, которые контактны с посетителями:");
        for (Animal animal : animals) {
            if (animal.GetClassification().equals("Herbo") && ((Herbo) animal).IsKind()) {
                System.out.println(animal.GetType() + " " + animal.GetName());
            }
        }
    }

    public int ShowZooFoodFactor() {
        int food_factor = 0;
        for (Animal animal : animals) {
            System.out.println(animal.GetType() + " " + animal.GetName() + " потребляет " + animal.GetFoodFactor() + " кг еды.");
            food_factor += animal.GetFoodFactor();
        }
        return food_factor;
    }

    public int GetAnimalsCount() {
        return animals.size();
    }

    public int GetInventoryCount() {
        return inventory.size();
    }
}
