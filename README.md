# WIN32 API 강의 차례
1. 윈도우 API 소개 및 자료형
2. 윈도우(창) 동작 과정 WinMain()
3. 버튼 콘트롤 (콘트롤=위젯)
4. 에디트 콘트롤
5. 리스트 콘트롤/콤보 콘트롤
6. 스태틱 콘트롤
7. 그래픽 (HDC)
8. 커스텀 콘트롤
9. 리스트뷰 콘트롤
10. 트리뷰 콘트롤
11. 기타 콘트롤 살펴보기
12. 대화상자 만들기 (샘플 프로그램 제작)
13. 프라퍼티 쉬트 (설치용)

# WIN32 API 강의 링크 (죠우저프님)
1. [WIN32 API 프로그래밍 강의 1 - 소개](https://www.youtube.com/watch?v=UfLe6q2K8JY&t=313s)
2. [WIN32 API 프로그래밍 강의 - WinMain](https://www.youtube.com/watch?v=7mVx3oiB7s4)
3. [WIN32 API 프로그래밍 강의 (버튼/에디트 콘트롤)](https://www.youtube.com/watch?v=OKDMCVRAn4w)
4. [WIN32 API 프로그래밍 - 리스트 콘트롤/콤보콘트롤 (1)](https://www.youtube.com/watch?v=PkYXuVddT9s)
5. [WIN32 API 프로그래밍 - 리스트 콘트롤/콤보콘트롤 (2)](https://www.youtube.com/watch?v=fvgJxRYsDUc)
6. [WIN32 API 프로그래밍 - 스태틱 콘트롤](https://www.youtube.com/watch?v=cVxQdzSf7p0)
7. [WIN32 API 프로그래밍 - GUI (HDC)](https://www.youtube.com/watch?v=2uBq4KOY3kU)
8. [WIN32 API 프로그래밍 - 커스텀 콘트롤 (1)](https://www.youtube.com/watch?v=dkTHR6wvzIk)
9. [WIN32 API 프로그래밍 - 8. 커스텀 콘트롤 (2) (11회)](https://www.youtube.com/watch?v=9ow4OxHulZ4)
10. [WIN32 API 프로그래밍 - 9. 리스트뷰 콘트롤 (12강)](https://www.youtube.com/watch?v=Eh6Emat__Mo)
11. [WIN32 API 프로그래밍 - 10. 트리뷰 콘트롤 (13강)](https://www.youtube.com/watch?v=QfXWyPIi0u8)
12. [WIN32 API 프로그래밍 - 11. 기타 콘트롤 살펴보기 (14강)](https://www.youtube.com/watch?v=vXgcFfmLiFc)
13. [WIN32 API 프로그래밍 - 12-1. 대화상자 만들기 (15강)](https://www.youtube.com/watch?v=VTsSd08eZt0)
14. [WIN32 API 프로그래밍 - 12-2. 모달형과 모달리스형 대화상자 (16강)](https://www.youtube.com/watch?v=_2IJRueNwYI)
15. [WIN32 API 프로그래밍 - 12-3. 버튼 그래픽으로 옷입히기 (17강)](https://www.youtube.com/watch?v=1YlcfYmAeqc)
16. [WIN32 API 프로그래밍 - 12-4. 대화상자 그래픽으로 옷입히기 (18강)](https://www.youtube.com/watch?v=YhUKSt-Bem4)
17. [WIN32 API 프로그래밍 - 13. 프라퍼티 쉬트 (19강)](https://www.youtube.com/watch?v=9vfKYd_n9Rs)

# WIN32 API 개념
- 윈도우즈 어플리케이션을 만들기 위해 os에서 제공하는 함수들이다.

# WIN32 API를 배우는 목적
- 가장 빠르고 실행코드가 작은 프로그램을 작성 할 수 있다.
- 의존성이 없어 PE윈도우에서도 실행이 된다.
- 다른 언어들은 서브시스템이나 배포패키지 (MFC)를 설치해야 동작한다. (ex) C#은 수백 메가 분량의 닷넷프레임웍을 설치해야 실행파일이 동작함.
- 윈도우즈 시스템을 이해하게 되어 C#이나 MFC 프로그래밍에 도움을 준다.



# WIN32 프로그램 포지션
- WIN32DLL모델.png

# WIN32 DLL
- kernel32.dll : 파일시스템, 프로세스, 쓰레드, 이벤트, 메모리, 기본문자열함수, 레지스트리
- user32.dll : 윈도우관리/대화상자, 메세지관리
- gdi32.dll : 화면 출력 (그래픽) 관련
- SHELL32.DLL : Shell 관련함수, ShellExecure
- SHLWAPI.DLL : Shell 관련함수, C언어 문자열관련 런타임함수
- NTDLL.DLL : C언어 문자열관련 런타임함수, memcpy, _allmul


# Total Commander 사용법
[Total Commander Download](https://www.ghisler.com/download.htm)  
[FileInfo Plugin Download](https://totalcmd.net/plugring/fileinfo.html)

1. Total Commander를 다운로드한다.
2. FileInfo Plugin을 다운로드해서 압축을 푼다.
3. 압축푼 파일 중 64bit인 경우 fileinfo.wtx64, 32bit인 경우 fileinfo.wtx 파일을 C:/windows/system32 폴더에 복사한다.
4. Total Commander 프로그램을 실행 후 맨 위 탭에서 환경설정 > 옵션에 들어간다.
5. 옵션에 들어간 후 왼쪽 목록에서 플러그인 항목을 클릭한다.
6. 플러그인 항목에서 리스터(내장 뷰어)플러그인을 클릭한다.
7. 아래 추가 버튼을 누른 후 system32 폴더에 복사된 fileinfo.wtx(64) 파일을 추가한다. 
8. 추가했으면 확인버튼을 누른다. 
