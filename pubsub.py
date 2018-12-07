iPUB:

(sanenv) lpeechar@~/JSM_MXP/VENV_PY/sanenv\>>
(sanenv) lpeechar@~/JSM_MXP/VENV_PY/sanenv\>>
(sanenv) lpeechar@~/JSM_MXP/VENV_PY/sanenv\>>
(sanenv) lpeechar@~/JSM_MXP/VENV_PY/sanenv\>>
(sanenv) lpeechar@~/JSM_MXP/VENV_PY/sanenv\>> python
Python 2.7.10 (default, Oct  6 2017, 22:29:07)
[GCC 4.2.1 Compatible Apple LLVM 9.0.0 (clang-900.0.31)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import zmq
>>> context = zmq.Context()
>>> pub = context.socket(zmq.PUB)
>>> pub.bind('tcp://127.0.0.1:1234')
>>> pub.send_multipart(['a', 'b'])
>>> pub.send_multipart(['c', 'd'])
>>> pub.send_multipart(['c', 'd1'])
>>> pub.send_multipart(['c', 'd2'])
>>> pub.send_multipart(['c', 'd7'])
>>> pub.send_multipart(['ck', 'd7'])
>>>

SUB:

    (sanenv) lpeechar@~/JSM_MXP/VENV_PY\>> python
Python 2.7.10 (default, Oct  6 2017, 22:29:07)
[GCC 4.2.1 Compatible Apple LLVM 9.0.0 (clang-900.0.31)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import zmq
>>> context = zmq.context()
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'module' object has no attribute 'context'
>>> context = zmq.Context()
>>> sub = context.socket(zmq.SUB)
>>> sub.setsockopt(zmq.SUBSCRIBE, '')
>>> sub.connect('tcp://127.0.0.1:1234')
>>> sub.recv_multipart()
['a', 'b']
>>> sub.recv_multipart()
['c', 'd']
>>>
>>>
>>>
>>> sub.recv_multipart()
['c', 'd1']
>>> sub.recv_multipart()
['c', 'd2']
>>> sub.recv_multipart()
['c', 'd7']
>>> sub.recv_multipart()
['ck', 'd7']
>>>
