//
//  LockExample.cpp
//
//  Created by jacketzhong on 14-9-10.
//  Copyright (c) 2014年 jacketzhong. All rights reserved.
//

#include <stdlib.h>
#include <unistd.h>
#include "redlock-cpp/redlock.h"

int main (int argc, char **argv) {
    CRedLock * dlm = new CRedLock();
    dlm->AddServerUrl("127.0.0.1", 5005);
    dlm->AddServerUrl("127.0.0.1", 5006);
    dlm->AddServerUrl("127.0.0.1", 5007);
    int hit = 0;
    int miss = 0;
    // 分布式锁的使用案例
    for (int i =0; i< 10000 ; i++) {
        CLock my_lock;
        bool flag = dlm->Lock("foo", 100, my_lock);
	
        if (flag) {
            //printf("获取成功, Acquired by client name:%s, res:%s, vttl:%d\n",
             //      my_lock.m_val, my_lock.m_resource, my_lock.m_validityTime);
            // do resource job
            //sleep(80);
	    hit++;
            dlm->Unlock(my_lock);
            // do other job
            //sleep(2);
        } else {
            //printf("获取失败, lock not acquired, name:%s\n", my_lock.m_val);
            //sleep(rand() % 3);
	    miss++;
        }
    }

    printf("Hits: %d --- Misses: %d", hit, miss);

    return 0;
}
