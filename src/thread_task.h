/**
 * ClassName: thread_task
 * Description: thread task
 * Author: Mark yunsheng.Liu
 * Date: 2021/05/21
 * Version: V1.0
 * QQ:120772981
 **/ 
class thread_task{
    public:
        typedef void task_fun(void*);
        thread_task(task_fun *pfun, void *pargs)
            :fun(pfun),
            args(pargs) {

        }

        ~thread_task(){

        }

        void do_work() {
            if(fun){
                fun(args);
            }
        }
    private:
        void *args;
        task_fun *fun;
};