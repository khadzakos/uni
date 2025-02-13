package hse.zoo.services;

import hse.zoo.models.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Component
public class Zoo {
    private final VetClinic clinic;
    private final List<Animal> animals = new ArrayList<>();
    private final List<Thing> things = new ArrayList<>();

    @Autowired
    public Zoo(VetClinic clinic) {
        this.clinic = clinic;
    }

    public void AddAnimal(Animal animal) {
        int number = animal.GetInventoryNumber();
        for (Animal a : animals) {
            if (a.GetInventoryNumber() == number) {
                System.out.println("Животное с таким инвентарным номером уже есть в зоопарке.");
                return;
            }
        }

        if (clinic.IsHealthy(animal)) {
            animals.add(animal);
            System.out.println(animal.GetType() + " " + animal.GetName() + " принят в зоопарк.");
        } else {
            System.out.println("К сожалению, " + animal.GetType() + " " + animal.GetName() + " не прошел проверку ветеринара и не может быть добавлен в зоопарк.");
        }
    }

    public void AddThing(Thing thing) {
        things.add(thing);
        System.out.println("Предмет " + thing.GetInventoryNumber() + " добавлен в инвентарь.");
    }

    public void ShowAnimals() {
        System.out.println("Животные в зоопарке:");
        for (Animal animal : animals) {
            System.out.println(animal.GetType() + " " + animal.GetName() + " - " + (animal.GetClassification().equals("Herbo") ? "Травоядное" : "Плотоядное"));
        }
    }

    public int ShowContactAnimals() {
        int count = 0;
        System.out.println("Животные в зоопарке, которые контактны с посетителями:");
        for (Animal animal : animals) {
            if (animal.GetClassification().equals("Herbo") && ((Herbo) animal).IsKind()) {
                System.out.println(animal.GetType() + " " + animal.GetName());
                count++;
            }
        }
        return count;
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
        return things.size();
    }

    public void ShowInventory() {
        System.out.println("Инвентарь животных:");
        for (Animal animal : animals) {
            System.out.println(animal.GetType() + " " + animal.GetName() + " - " + animal.GetInventoryNumber());
        }

        System.out.println("Инвентарь вещей:");
        for (Thing thing : things) {
            System.out.println(thing.GetType() + " - " + thing.GetInventoryNumber());
        }
    }

    public Animal FindAnimalByNumber(int number) {
        for (Animal animal : animals) {
            if (animal.GetInventoryNumber() == number) {
                return animal;
            }
        }
        return null;
    }

    public Thing FindThingByNumber(int number) {
        for (Thing thing : things) {
            if (thing.GetInventoryNumber() == number) {
                return thing;
            }
        }
        return null;
    }

    public void Clear() {
        animals.clear();
        things.clear();
    }
}
