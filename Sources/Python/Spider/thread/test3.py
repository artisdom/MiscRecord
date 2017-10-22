#!/usr/bin/env python
# -*- coding:utf-8 -*-
import Queue
import sys
import requests
import os
import threading
import time

class Worker(threading.Thread):  # ����������
  def __init__(self, workQueue, resultQueue, **kwds):
    threading.Thread.__init__(self, **kwds)
    self.setDaemon(True)
    self.workQueue = workQueue
    self.resultQueue = resultQueue


  def run(self):
    while 1:
      try:
        callable, args, kwds = self.workQueue.get(False)  # get task
        res = callable(*args, **kwds)
        self.resultQueue.put(res)  # put result
      except Queue.Empty:
        break

class WorkManager:  # �̳߳ع���,����
  def __init__(self, num_of_workers=10):
    self.workQueue = Queue.Queue()  # �������
    self.resultQueue = Queue.Queue()  # �������Ķ���
    self.workers = []
    self._recruitThreads(num_of_workers)

  def _recruitThreads(self, num_of_workers):
    for i in range(num_of_workers):
      worker = Worker(self.workQueue, self.resultQueue)  # ���������߳�
      self.workers.append(worker)  # ���뵽�̶߳���


  def start(self):
    for w in self.workers:
      w.start()

  def wait_for_complete(self):
    while len(self.workers):
      worker = self.workers.pop()  # �ӳ���ȡ��һ���̴߳�������
      worker.join()
      if worker.isAlive() and not self.workQueue.empty():
        self.workers.append(worker)  # ���¼����̳߳���
    print 'All jobs were complete.'


  def add_job(self, callable, *args, **kwds):
    self.workQueue.put((callable, args, kwds))  # ���������м�������

  def get_result(self, *args, **kwds):
    return self.resultQueue.get(*args, **kwds)


def download_file(url):
  #print 'beg download', url
  # requests.get(url).text



try:
    num_of_threads = int(sys.argv[1])
except:
    num_of_threads = 10
_st = time.time()
wm = WorkManager(num_of_threads)
print num_of_threads
urls = ['http://www.baidu.com'] * 1000
for i in urls:
    wm.add_job(download_file, i)
wm.start()
wm.wait_for_complete()
print time.time() - _st

