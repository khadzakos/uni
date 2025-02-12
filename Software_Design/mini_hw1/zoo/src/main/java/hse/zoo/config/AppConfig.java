package hse.zoo.config;

import hse.zoo.services.*;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@ComponentScan(basePackages = "hse.zoo")  // Укажи свой пакет
public class AppConfig {

    @Bean
    public VetClinic vetClinic() {
        return new VetClinic();
    }

    @Bean
    public Zoo zoo(VetClinic vetClinic) {
        return new Zoo(vetClinic);
    }
}