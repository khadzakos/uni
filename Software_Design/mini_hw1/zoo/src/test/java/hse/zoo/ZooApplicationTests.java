package hse.zoo;

import hse.zoo.config.AppConfig;
import hse.zoo.models.*;
import hse.zoo.services.Zoo;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest(classes = AppConfig.class)
class ZooApplicationTests {
    @Autowired
    private Zoo zoo;

    @BeforeEach
    void setUp() {
        zoo.Clear();
    }

    @Test
    void testAnimalCreation() {
        Animal animal = new Animal("George", "Monkey", "Herbo", 5, 1, true);
        assertEquals("George", animal.GetName());
        assertEquals("Monkey", animal.GetType());
        assertEquals("Herbo", animal.GetClassification());
        assertEquals(5, animal.GetFoodFactor());
        assertEquals(1, animal.GetInventoryNumber());
        assertTrue(animal.IsHealthy());
    }

    @Test
    void testAnimalHealthStatus() {
        Animal healthyAnimal = new Animal("George", "Monkey", "Herbo", 5, 1, true);
        Animal unhealthyAnimal = new Animal("Peter", "Monkey", "Herbo", 5, 2, false);
        assertTrue(healthyAnimal.IsHealthy());
        assertFalse(unhealthyAnimal.IsHealthy());
    }

    @Test
    void testAnimalFoodFactor() {
        Animal animal = new Animal("George", "Monkey", "Herbo", 5, 1, true);
        assertEquals(5, animal.GetFoodFactor());
    }

    @Test
    void testAnimalInventoryNumber() {
        Animal animal = new Animal("George", "Monkey", "Herbo", 5, 1, true);
        assertEquals(1, animal.GetInventoryNumber());
    }

    @Test
    void testPredatorCreation() {
        Predator predator = new Predator("George", "Tiger", 100, 5, true);
        assertEquals("George", predator.GetName());
        assertEquals("Tiger", predator.GetType());
        assertEquals("Predator", predator.GetClassification());
        assertEquals(100, predator.GetFoodFactor());
        assertEquals(5, predator.GetInventoryNumber());
        assertTrue(predator.IsHealthy());
    }

    @Test
    void testTigerCreation() {
        Tiger tiger = new Tiger("George", 5, 1, true);
        assertEquals("George", tiger.GetName());
        assertEquals("Тигр", tiger.GetType());
        assertEquals("Predator", tiger.GetClassification());
        assertEquals(5, tiger.GetFoodFactor());
        assertEquals(1, tiger.GetInventoryNumber());
        assertTrue(tiger.IsHealthy());
    }

    @Test
    void testWolfCreation() {
        Wolf wolf = new Wolf("George", 5, 1, true);
        assertEquals("George", wolf.GetName());
        assertEquals("Волк", wolf.GetType());
        assertEquals("Predator", wolf.GetClassification());
        assertEquals(5, wolf.GetFoodFactor());
        assertEquals(1, wolf.GetInventoryNumber());
        assertTrue(wolf.IsHealthy());
    }

    @Test
    void addAnimal() {
        Animal monkey = new Monkey("George", 5, 1, true, 7);
        zoo.AddAnimal(monkey);
        assertEquals(1, zoo.GetAnimalsCount());
        assertEquals("George", zoo.FindAnimalByNumber(1).GetName());
    }

    @Test
    void addDuplicateAnimal() {
        Animal monkey = new Monkey("George", 5, 1, true, 7);
        zoo.AddAnimal(monkey);
        zoo.AddAnimal(monkey);
        assertEquals(1, zoo.GetAnimalsCount());
    }

    @Test
    void showAnimals() {
        Animal monkey = new Monkey("George", 5, 1, true, 7);
        zoo.AddAnimal(monkey);
        assertNotEquals(0, zoo.GetAnimalsCount());
    }

    @Test
    void showContactAnimals() {
        Animal monkey_1 = new Monkey("George", 5, 1, true, 7);
        Animal monkey_2 = new Monkey("Peter", 5, 2, true, 4);
        Animal rabbit = new Rabbit("Bugs", 3, 3, true, 5);
        zoo.AddAnimal(monkey_1);
        zoo.AddAnimal(monkey_2);
        zoo.AddAnimal(rabbit);

        assertEquals(3, zoo.GetAnimalsCount());
        assertEquals(1, zoo.ShowContactAnimals());
    }

    @Test
    void showZooFoodFactor() {
        Animal monkey = new Monkey("George", 5, 1, true, 7);
        Animal rabbit = new Rabbit("Bugs", 3, 2, true, 5);
        zoo.AddAnimal(monkey);
        zoo.AddAnimal(rabbit);
        assertEquals(8, zoo.ShowZooFoodFactor());
    }

    @Test
    void findAnimalByNumber() {
        Animal monkey = new Monkey("George", 5, 1, true, 7);
        zoo.AddAnimal(monkey);
        assertNotNull(zoo.FindAnimalByNumber(1));
        assertEquals("George", zoo.FindAnimalByNumber(1).GetName());
    }

    @Test
    void findNonExistentAnimalByNumber() {
        assertNull(zoo.FindAnimalByNumber(99));
    }

    @Test
    void addThing() {
        Thing thing = new Computer(10);
        zoo.AddThing(thing);
        assertEquals(1, zoo.GetInventoryCount());
    }

    @Test
    void findThingByNumber() {
        Thing thing = new Table(101);
        zoo.AddThing(thing);
        assertNotNull(zoo.FindThingByNumber(101));
    }

    @Test
    void findNonExistentThingByNumber() {
        assertNull(zoo.FindThingByNumber(999));
    }

    @Test
    void showInventory() {
        Animal monkey = new Monkey("George", 5, 1, true, 7);
        Thing thing = new Computer(10);
        zoo.AddAnimal(monkey);
        zoo.AddThing(thing);
        assertEquals(1, zoo.GetAnimalsCount());
        assertEquals(1, zoo.GetInventoryCount());
    }

}