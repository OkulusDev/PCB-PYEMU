#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Определение базового класса компонента
typedef struct {
    char name[20];
    float value;
} Component;

// Определение класса линейного компонента, наследующего от базового класса
typedef struct {
    Component base;
    float voltage;
} LinearComponent;

// Определение класса провода
typedef struct {
    char name[20];
    Component* startComponent;
    Component* endComponent;
} Wire;

// Определение класса платы
typedef struct {
    char name[20];
    LinearComponent** components;
    Wire** wires;
    int numComponents;
    int numWires;
    float powerConsumption;
} PCB;

// Функция для создания компонента
Component* createComponent(const char* name, float value) {
    Component* component = (Component*)malloc(sizeof(Component));
    sprintf(component->name, "%s", name);
    component->value = value;
    return component;
}

// Функция для создания линейного компонента
LinearComponent* createLinearComponent(const char* name, float value, float voltage) {
    LinearComponent* component = (LinearComponent*)malloc(sizeof(LinearComponent));
    sprintf(component->base.name, "%s", name);
    component->base.value = value;
    component->voltage = voltage;
    return component;
}

// Функция для создания провода
Wire* createWire(const char* name, Component* startComponent, Component* endComponent) {
    Wire* wire = (Wire*)malloc(sizeof(Wire));
    sprintf(wire->name, "%s", name);
    wire->startComponent = startComponent;
    wire->endComponent = endComponent;
    return wire;
}

// Функция для создания платы
PCB* createPCB(const char* name) {
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    sprintf(pcb->name, "%s", name);
    pcb->components = NULL;
    pcb->wires = NULL;
    pcb->numComponents = 0;
    pcb->numWires = 0;
    pcb->powerConsumption = 0.0;
    return pcb;
}

// Функция для добавления компонента на плату
void addComponent(PCB* pcb, LinearComponent* component) {
    pcb->numComponents++;
    pcb->components = (LinearComponent**)realloc(pcb->components, pcb->numComponents * sizeof(LinearComponent*));
    pcb->components[pcb->numComponents - 1] = component;
}

// Функция для добавления провода на плату
void addWire(PCB* pcb, Wire* wire) {
    pcb->numWires++;
    pcb->wires = (Wire**)realloc(pcb->wires, pcb->numWires * sizeof(Wire*));
    pcb->wires[pcb->numWires - 1] = wire;
}

// Функция для вычисления потребления энергии на плате
float calculatePowerConsumption(PCB* pcb) {
    float totalPower = 0.0;
    for (int i = 0; i < pcb->numComponents; i++) {
        totalPower += pcb->components[i]->voltage * pcb->components[i]->base.value;
    }
    pcb->powerConsumption = totalPower;
    return totalPower;
}

// Функция для вывода информации о плате
void printPCB(PCB* pcb) {
    printf("PCB Name: %s\n", pcb->name);
    printf("Components:\n");
    for (int i = 0; i < pcb->numComponents; i++) {
        printf("- Name: %s, Value: %.2f, Voltage: %.2f\n", pcb->components[i]->base.name, pcb->components[i]->base.value, pcb->components[i]->voltage);
    }
    printf("Wires:\n");
    for (int i = 0; i < pcb->numWires; i++) {
        printf("- Name: %s, Start Component: %s, End Component: %s\n", pcb->wires[i]->name, pcb->wires[i]->startComponent->name, pcb->wires[i]->endComponent->name);
    }
    printf("Power Consumption: %.2f\n", pcb->powerConsumption);
}

// Функция для вывода платы в ASCII-графике
void printPCBAscii(PCB* pcb) {
    printf("PCB Name: %s\n", pcb->name);
    printf("Components:\n");
    for (int i = 0; i < pcb->numComponents; i++) {
        printf("   %s\n", pcb->components[i]->base.name);
    }
    printf("Wires:\n");
    for (int i = 0; i < pcb->numWires; i++) {
        printf("   %s\n", pcb->wires[i]->name);
    }
}

// Функция для изменения значения компонента
void modifyComponentValue(Component* component, float newValue) {
    component->value = newValue;
}

int main() {
    PCB* pcb = createPCB("MyPCB");

    int choice;
    do {
        printf("Menu:\n");
        printf("1. Add Component\n");
        printf("2. Add Wire\n");
        printf("3. Modify Component Value\n");
        printf("4. Print PCB\n");
        printf("5. Print PCB (ASCII)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[20];
                float value;
                printf("Enter component name: ");
                scanf("%s", name);
                printf("Enter component value: ");
                scanf("%f", &value);
                LinearComponent* component = createLinearComponent(name, value, 0.0);
                addComponent(pcb, component);
                printf("Component added successfully.\n");
                break;
            }
            case 2: {
                char name[20];
                char startComponentName[20];
                char endComponentName[20];
                printf("Enter wire name: ");
                scanf("%s", name);
                printf("Enter start component name: ");
                scanf("%s", startComponentName);
                printf("Enter end component name: ");
                scanf("%s", endComponentName);

                // Find start and end components in the PCB
                Component* startComponent = NULL;
                Component* endComponent = NULL;
                for (int i = 0; i < pcb->numComponents; i++) {
                    if (strcmp(pcb->components[i]->base.name, startComponentName) == 0) {
                        startComponent = &(pcb->components[i]->base);
                    }
                    if (strcmp(pcb->components[i]->base.name, endComponentName) == 0) {
                        endComponent = &(pcb->components[i]->base);
                    }
                }

                if (startComponent != NULL && endComponent != NULL) {
                    Wire* wire = createWire(name, startComponent, endComponent);
                    addWire(pcb, wire);
                    printf("Wire added successfully.\n");
                } else {
                    printf("One or both of the components not found.\n");
                }
                break;
            }
            case 3: {
                char componentName[20];
                float newValue;
                printf("Enter component name: ");
                scanf("%s", componentName);
                printf("Enter new value: ");
                scanf("%f", &newValue);

                // Find the component in the PCB
                Component* component = NULL;
                for (int i = 0; i < pcb->numComponents; i++) {
                    if (strcmp(pcb->components[i]->base.name, componentName) == 0) {
                        component = &(pcb->components[i]->base);
                        break;
                    }
                }

                if (component != NULL) {
                    modifyComponentValue(component, newValue);
                    printf("Component value modified successfully.\n");
                } else {
                    printf("Component not found.\n");
                }
                break;
            }
            case 4: {
                printPCB(pcb);
                break;
            }
            case 5: {
                printPCBAscii(pcb);
                break;
            }
            case 0: {
                printf("Exiting...\n");
                break;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
        printf("\n");
    } while (choice != 0);

    // Освобождение памяти
    for (int i = 0; i < pcb->numComponents; i++) {
        free(pcb->components[i]);
    }
    free(pcb->components);
    for (int i = 0; i < pcb->numWires; i++) {
        free(pcb->wires[i]);
    }
    free(pcb->wires);
    free(pcb);

    return 0;
}
