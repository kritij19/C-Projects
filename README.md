# C-Projects
This repository contains the following projects:

1. **Audio volume modifier** -  
Inputs a .wav file and returns a .wav file with modified volume on the basis of a user inputted factor.

```bash 
make Audio_Volume_Modifier
```
---    
2. **Filters** -  
Executes the following filters on .bmp images:  
              *i) Grayscale*  
              *ii) Sepia*  
              *iii) Reflection*    
              *iv) Blur*   
              *v) Edge highlighting*  


```bash 
make Filters
```                

3. **Tideman Election** -   
Implements the tideman algorithm for conducting an election.  
```bash 
make Tideman_Elections
```  
---
4. **Runoff Election** -   
Implements the instant runoff system to conduct an election.

```bash 
make Runoff_elections
```  
---
5. **Readability Test** -   
Determines the (U.S.) grade level required to understand a given text. Uses Coleman-Liau index. 

```bash 
make Readability_Test
```

---

>:warning: working requires Premake5 installed

* wget https://github.com/premake/premake-core/releases/download/v5.0.0-alpha16/premake-5.0.0-alpha16-linux.tar.gz

* tar -xvzf premake-5.0.0-alpha16-linux.tar.gz -c /usr/bin