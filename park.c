#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 3
typedef struct {
    char license_plate[10];
    time_t arrival_time;
    time_t departure_time;
} Car;

typedef struct {
    Car stack[MAXSIZE];
    int top;
} Stack;

typedef struct {
    Car queue[MAXSIZE];
    int front;
    int rear;
} Queue;

void InitStack(Stack *s) {
    s->top = -1;
}

int StackEmpty(Stack *s) {
    return s->top == -1;
}

int StackFull(Stack *s) {
    return s->top == MAXSIZE - 1;
}

void Push(Stack *s, Car c) {
    if (!(StackFull(s))) {
        s->stack[++s->top] = c;
    } else {
        printf("停车场已满\n");
    }
}

Car Pop(Stack *s) {
    Car c = {"", -1, -1};
    if (!StackEmpty(s)) {
        c = s->stack[s->top--];
    } else {
        printf("停车场为空\n");
    }
    return c;
}

void InitQueue(Queue *q) {
    q->rear = q->front = 0;
}

int QueueEmpty(Queue *q) {
    return q->front == q->rear;
}

int QueueFull(Queue *q) {
    return (q->rear + 1) % MAXSIZE == q->front;
}

void EnQueue(Queue *q, Car c) {
    if (!QueueFull(q)) {
        q->queue[q->rear] = c;
        q->rear = (q->rear + 1) % MAXSIZE;
    } else {
        printf("便道已经满了\n");
    }
}

Car DeQueue(Queue *q) {
    Car c = {"", -1, -1};
    if (!QueueEmpty(q)) {
        c = q->queue[q->front];
        q->front = (q->front + 1) % MAXSIZE;
    } else {
        printf("便道为空\n");
    }
    return c;
}

void ShowStatus(Stack s, Queue q) {
    printf("停车场内车辆情况：\n");
    for (int i = s.top; i >= 0; i--) {
        printf("车牌号：%s, 到达时间：%s\n", s.stack[i].license_plate, ctime(&s.stack[i].arrival_time));
    }
    printf("便道上等待车辆情况：\n");
    for (int i = q.front; i != q.rear; i = (i + 1) % MAXSIZE) {
        printf("车牌号：%s, 到达时间：%s\n", q.queue[i].license_plate, ctime(&q.queue[i].arrival_time));
    }
}

long CalculateFee(time_t stay_time) {
    long fee = (long)(stay_time); // 假设每秒1元
    return fee;
}

void InitSystem(Stack *parking_lot, Queue *waiting_area) {
    InitStack(parking_lot);
    InitQueue(waiting_area);
}
// 创新点：实时记录停车时间，更符合停车逻辑
time_t getCurrentTime() {
    time_t now = time(NULL); // 获取当前时间
    return now;
}

void CarArrival(Stack *parking_lot, Queue *waiting_area) {
    Car new_car;
    printf("请输入车牌号码：");
    scanf("%9s", new_car.license_plate); // 避免缓冲区溢出
    new_car.arrival_time = getCurrentTime();
    printf("车辆到达时间：%s", ctime(&new_car.arrival_time)); // 使用ctime函数打印可读的时间
    if(QueueFull(waiting_area)){
        printf("便道已满，请选择别的停车场。\n");
    }
    else if (StackFull(parking_lot)) {
        printf("停车场已满，车辆 %s 在便道等待。\n", new_car.license_plate);
        EnQueue(waiting_area, new_car);
    } else {
        Push(parking_lot, new_car);
        printf("车辆 %s 已停入停车场。\n", new_car.license_plate);
    }
}

void CarDeparture(Stack *parking_lot, Queue *waiting_area) {
    int position;
    time_t departure_time;
    printf("请输入离开车辆的位置（1~%d）：", parking_lot->top + 1);
    scanf("%d", &position);
    if (position < 1 || position > parking_lot->top + 1) {
        printf("无效位置\n");
        return;
    }

    departure_time = getCurrentTime();
    printf("车辆离开时间：%s", ctime(&departure_time));

    Stack temp_stack;
    InitStack(&temp_stack);

    while (parking_lot->top + 1 != position) {
        Push(&temp_stack, Pop(parking_lot));
    }

    Car car_to_leave = Pop(parking_lot);
    car_to_leave.departure_time = departure_time;
    time_t time_diff = departure_time - car_to_leave.arrival_time;
    printf("车辆 %s 停车时间 %ld秒，应缴纳费用 %ld。\n", car_to_leave.license_plate, time_diff,
           CalculateFee(time_diff));

    while (!StackEmpty(&temp_stack)) {
        Push(parking_lot, Pop(&temp_stack));
    } // 临时栈中的车按原顺序返回停车场

    if (!QueueEmpty(waiting_area)) {
        Car entering_car = DeQueue(waiting_area);
        entering_car.arrival_time = getCurrentTime(); // 更新新的到达时间
        Push(parking_lot, entering_car);
        printf("便道车辆 %s 进入停车场，新到达时间：%s", entering_car.license_plate, ctime(&entering_car.arrival_time));
    } // 便道车补位
}

int main() {
    Stack parking_lot;
    Queue waiting_area;
    InitSystem(&parking_lot, &waiting_area);

    int choice;
    while (1) {
        printf("请输入操作命令（1-到达，2-离开，3-显示状态，4-退出）：");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            CarArrival(&parking_lot, &waiting_area);
            break;
        case 2:
            CarDeparture(&parking_lot, &waiting_area);
            break;
        case 3:
            ShowStatus(parking_lot, waiting_area);
            break;
        case 4:
            printf("正在退出系统...\n");
            return 0;
        default:
            printf("无效的命令，请重新输入。\n");
        }
    }
}
