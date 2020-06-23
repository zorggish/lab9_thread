#ifndef SORTTHREAD_H
#define SORTTHREAD_H

#include <QThread>
#include <QRandomGenerator>
#include <QDebug>

class SortThread : public QThread
{
    Q_OBJECT
public:
    int array[500000];

    void randomize()
    {
        /**
         * @brief Генерация массива
         */
        QRandomGenerator random;

        for(int i = 0; i < 500000; i++)
            array[i] = random.bounded(0, 500000);
    }

    void run()
    {
        /**
         * @brief Сортировка массива методом пузырька
         * @emit iterationComplete Каждые 100 итераций основного цикла
         */
        int temp;
        for(int i = 0; i < 500000; i++)
        {
            for(int j = 0; j < 500000-1; j++)
            {
                if(array[j] > array[j+1])
                {
                    temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                }
            }
            if(i%100 == 0)
                emit iterationComplete(array, i);
        }
    }

signals:
    void iterationComplete(int *, int);
};

#endif // SORTTHREAD_H
