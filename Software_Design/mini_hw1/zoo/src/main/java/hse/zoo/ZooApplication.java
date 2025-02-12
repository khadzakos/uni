package hse.zoo;

import hse.zoo.config.AppConfig;
import hse.zoo.models.*;
import hse.zoo.services.Zoo;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

import java.util.InputMismatchException;
import java.util.Scanner;

public class ZooApplication {
	public static void main(String[] args) {
		ApplicationContext context = new AnnotationConfigApplicationContext(AppConfig.class);
		Zoo zoo = context.getBean(Zoo.class);

		Scanner scanner = new Scanner(System.in);
		System.out.println("Добро пожаловать ERP-систему зоопарка!");
		while (true) {
			try {
				System.out.println("Выберите действие:");
				System.out.println("1. Добавить животное");
				System.out.println("2. Показать животных");
				System.out.println("3. Показать контактных животных");
				System.out.println("4. Показать необходимое количество питания");
				System.out.println("5. Добавить предмет");
				System.out.println("6. Показать инвентарь зоопарка");
				System.out.println("7. Найти животное по номеру");
				System.out.println("8. Найти предмет по номеру");
				System.out.println("9. Выйти");

				int choice = scanner.nextInt();
				scanner.nextLine();

				switch (choice) {
					case 1:
						System.out.println("Введите имя животного:");
						String name = scanner.nextLine();
						System.out.println("Введите номер животного:\n 1. Обезьяна\n 2. Кролик\n 3. Тигр\n 4. Вокл\n");
						String type = scanner.nextLine();
						int typeInt = Integer.parseInt(type);
						if (typeInt < 1 || typeInt > 4) {
							System.out.println("Такого номера нет в списке.");
							break;
						}
						System.out.println("Введите сколько питания потребляет животное:");
						int food = scanner.nextInt();
						scanner.nextLine();
						System.out.println("Введите инвентарный номер животного:");
						int number = scanner.nextInt();
						scanner.nextLine();
						System.out.println("Животное здорово? (true/false)");
						boolean isHealthy = scanner.nextBoolean();
						scanner.nextLine();

						int kindness = 0;
						if (typeInt == 1 || typeInt == 2) {
							System.out.println("Введите уровень доброты животного(от 1 до 10):");
							kindness = scanner.nextInt();
							if (kindness < 1 || kindness > 10) {
								System.out.println("Уровень доброты должен быть от 1 до 10.");
								break;
							}
							scanner.nextLine();
						}
						switch (typeInt) {
							case 1:
								Animal monkey = new Monkey(name, food, number, isHealthy, kindness);
								zoo.AddAnimal(monkey);
								break;
							case 2:
								Animal rabbit = new Rabbit(name, food, number, isHealthy, kindness);
								zoo.AddAnimal(rabbit);
								break;
							case 3:
								Animal tiger = new Tiger(name, food, number, isHealthy);
								zoo.AddAnimal(tiger);
								break;
							case 4:
								Animal wolf = new Wolf(name, food, number, isHealthy);
								zoo.AddAnimal(wolf);
								break;
						}
						break;
					case 2:
						zoo.ShowAnimals();
						break;
					case 3:
						zoo.ShowContactAnimals();
						break;
					case 4:
						int foodFactor = zoo.ShowZooFoodFactor();
						System.out.println("Необходимое количество питания(кг): " + foodFactor);
						break;
					case 5:
						System.out.println("Введите тип предмета:");
						String thingType = scanner.nextLine();
						int thingNumber = scanner.nextInt();
						scanner.nextLine(); // consume newline
						Thing thing = new Thing(thingType, thingNumber);
						zoo.AddThing(thing);
						break;
					case 6:
						zoo.ShowInventory();
						break;
					case 7:
						System.out.println("Введите инвентарный номер животного:");
						int animalNumber = scanner.nextInt();
						scanner.nextLine(); // consume newline
						zoo.FindAnimalByNumber(animalNumber).ifPresentOrElse(
								a -> System.out.println("Найдено: " + a.GetType() + " " + a.GetName()),
								() -> System.out.println("Животное не найдено")
						);
						break;
					case 8:
						System.out.println("Введите инвентарный номер предмета:");
						int thingInventoryNumber = scanner.nextInt();
						scanner.nextLine(); // consume newline
						zoo.FindThingByNumber(thingInventoryNumber).ifPresentOrElse(
								t -> System.out.println("Найдено: " + t.GetType()),
								() -> System.out.println("Предмет не найден")
						);
						break;
					case 9:
						System.out.println("До свидания!");
						scanner.close();
						return;
					default:
						System.out.println("Такого действия нет.");
				}
			} catch (InputMismatchException e) {
				System.out.println("Необходимо ввести число.");
				scanner.nextLine(); // consume the invalid input
			} catch (Exception e) {
				System.out.println("Произошла ошибка: " + e.getMessage());
			}
		}
	}
}