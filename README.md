# ipcAssignment
다음과 같은 명령어를 작성해주세요.
<pre>
  <code>
    $ git update-index --assume-unchanged ipc2023/ipc2023.vcxproj
    $ git update-index --assume-unchanged ipc2023/ipc2023.vcxproj.filters
  </code>
</pre>
이는 개인 머신별로 설정될 WinPcap 등의 경로명이 달라져도 그 경로명이 commit되는 것을 방지하기 위함입니다.
