# -*- coding: utf-8 -*-  

import urllib2  
import urllib  
import re  
import os
from bs4 import BeautifulSoup 
#����ٶȺ���
url='http://www.website.com'
def urlparse(data,sub):
    #����
    # m=urllib2.urlopen(url).read()
    soup=BeautifulSoup(data,'lxml')
    # print soup.original_encoding
    for x in soup.find_all('a'):
        pic=x.get('href')
        if pic==None:continue
        if pic[0]=='#' or pic[0:4]=='java':continue
        elif cmp(pic[0:7],'http://')==0:
            # print pic
            if pic.endswith('/'):filename=pic+'index.html'
            else:filename=pic+'/index.html'
            # if  not pic.endswith('/'):filename=pic+'/index.html'
            filename=filename.replace('http://','');
            # filename=filename.replace('/','_');
            # print filename
        else:
            if not pic.startswith('/'):
                sub=sub.replace('http://','');
                # print sub,'----'
                subpath=sub.split('/')
                # print sub,'----'
                subpath='/'.join(subpath[0:-1])
                pic='http://'+subpath+'/'+pic
            else:pic=url+pic
            if not pic.endswith('.html'):
                filename=pic+'index.html'
            else:filename=pic
            # filename=url+filename
            filename=filename.replace('http://','')
            filename=filename.replace('?','_')
        filename=filename.replace(' ','_')
        # print filename
        if filename.find('website.com')==-1:continue
        path=filename.split('/')
        path='/'.join(path[0:-1])
        if not os.path.exists(path):os.makedirs(path)
        if os.path.exists(filename):continue
        try:
            link=urllib2.urlopen(pic)
        except: print filename+' timeout';continue
        filelist=open('urllist.txt','a+')
        filelist.write(filename+'\n');
        filelist.close();
        # print filename
        if link:
            ff=open(filename,'wb')
            try:
                buffer=link.read()
            except:print 'fail';continue
            ff.write(buffer)
            ff.close()
def urlimage(data):
    #����
    # m=urllib2.urlopen(url).read()
    soup=BeautifulSoup(data,'lxml')
    # print soup.original_encoding
    for x in soup.find_all('img'):
        pic=x.get('src')
        # print pic
        if pic==None:continue
        if pic[0]=='#' or pic[0:4]=='java':continue
        else:
            if not pic.startswith('/'):
                print pic
            else:pic=url+pic
            filename=pic
            # filename=url+filename
            filename=filename.replace('http://','');
            filename=filename.replace('?','_');
        # print pic,' '+filename
        path=filename.split('/')
        path='/'.join(path[0:-1])
        if not os.path.exists(path):os.makedirs(path)
        if os.path.exists(filename):continue
        try:
            link=urllib2.urlopen(pic)
        except: print filename+' timeout';continue
        # filelist=open('imagelist.txt','a+')
        # filelist.write(filename+'\n');
        # filelist.close();
        print filename
        if link:
            ff=open(filename,'wb')
            try:
                buffer=link.read()
            except:print 'fail';continue
            ff.write(buffer)
            ff.close()

# m=urllib2.urlopen(url).read()
# urlparse(m,url)
f=open('urllist.txt','r')
lines=f.readlines()
print len(lines)
start=14320
for x in lines[start:]:
    if not x:print 'None';continue
    print x
    print '--------------------------------------------'
    data=open(x[0:-1]).read()
    urlparse(data,x[0:-1])
print len(lines)
# for x in f.readlines():
    # print x
    # print '--------------------------------------------'
    # data=open(x[0:-1]).read()
    # urlimage(data)