当你使用nginx将浏览器的内容代理

(eg:http:1.1.1.1:8000/index.html)

那么,访问浏览的端口就从8000端口转到了80端口

浏览器请求其他资源就会有跨域问题,

浏览器向服务器发起get/post请求也会有跨域问题.

