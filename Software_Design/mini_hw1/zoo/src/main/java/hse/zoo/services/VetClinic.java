package hse.zoo.services;

import hse.zoo.models.Animal;
import org.springframework.stereotype.Service;

@Service
public class VetClinic {
    public boolean IsHealthy(Animal animal) {
        return animal.IsHealthy();
    }
}
