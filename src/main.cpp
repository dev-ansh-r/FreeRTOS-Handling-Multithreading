#include <Arduino.h>

int count1 = 0;
int count2 = 0;

TaskHandle_t task1Handle1=NULL;

void task1(void *parameter){
    for(;;){
      Serial.println("Task 1");
      Serial.println(count1++);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
  void task2(void *parameter){
    for(;;){
      Serial.println("Task 2");
      Serial.println(count2++);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }


void setup() {
  Serial.begin(9600);
  xTaskCreate(
    task1, /* Task function. */
    "Task 1", /* name of task. */
    10000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL); /* Task handle to keep track of created task */

  xTaskCreate(
    task2, /* Task function. */
    "Task 2", /* name of task. */
    10000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL); /* Task handle to keep track of created task */
}

void superimportanttask(void *parameter){
  for(;;){
    vTaskSuspendAll();
    Serial.println("Super important task");
    xTaskResumeAll();
  }
}
void loop() {
  if(count1 == 30 && task1Handle1!=NULL){
    vTaskDelete(task1Handle1);
  }
  if(count2 == 15){
    xTaskCreate(
      superimportanttask, /* Task function. */
      "Super important task", /* name of task. */
      10000, /* Stack size of task */
      NULL, /* parameter of the task */
      1, /* priority of the task */
      NULL); /* Task handle to keep track of created task */
  }
  }