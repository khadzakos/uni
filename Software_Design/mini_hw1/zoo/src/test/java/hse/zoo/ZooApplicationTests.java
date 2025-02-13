package hse.zoo;

import hse.zoo.config.AppConfig;
import hse.zoo.models.Animal;
import hse.zoo.models.Monkey;
import hse.zoo.models.Rabbit;
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
    void addAnimal() {
        Animal monkey = new Monkey("George", 5, 1, true, 7);
        zoo.AddAnimal(monkey);
        assertEquals(1, zoo.GetAnimalsCount());
        assertEquals("George", zoo.FindAnimalByNumber(1).GetName());
    }

    @Test
    void showAnimals() {
        Animal monkey = new Monkey("George", 5, 1, true, 7);
        zoo.AddAnimal(monkey);
        assertFalse((zoo.GetAnimalsCount() == 0));
    }

    @Test
    void showContactAnimals() {
        Animal monkey_1 = new Monkey("George", 5, 1, true, 7);
        Animal monkey_2 = new Monkey("Peter", 5, 2, true, 4);
        Animal rabbit = new Rabbit("Bugs", 3, 3, true, 5);
        zoo.AddAnimal(monkey_1);
        zoo.AddAnimal(monkey_2);
        zoo.AddAnimal(rabbit);

        assertTrue((zoo.GetAnimalsCount() == 3));
        assertTrue((zoo.ShowContactAnimals() == 1));
    }

    @Test
    void findAnimalByNumber() {
        Animal monkey = new Monkey("George", 5, 1, true, 7);
        zoo.AddAnimal(monkey);
        assertTrue((zoo.FindAnimalByNumber(1) != null));
        assertEquals("George", zoo.FindAnimalByNumber(1).GetName());
    }
}