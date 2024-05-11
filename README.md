# ASC Tema 3

#### Daraban Albert-Timotei

## Implementare

### BLAS

Am folosit functiile de inmultire pentru matrici generice/triunghiurale din bibloteca BLAS si doua matrici ajutatoare pentru rezultate intermediare.

### Ne-optimizat

Am facut functii pentru toate tipurile de inmultiri necesare: superior/sub triunghurale si imultire pe matrici generale. Si pentru adunarea a matricilor. Am folosit mai multe matricii intermediare.

### Optimizat

Am pornit de la implementarea optimzata. Am calculat sumele partile in variabile marcate register. Am schimbat inmultire intr un pe blocuri pentru a facilita accesul la cache. Am schimbat accesul de memorie de la in indexi la lucru cu pointeri.

## Memorie

Am o eroare singura eroare (``Syscall param msync(start) points to uninitialised byte(s)``) la versiunea optimizata detectata de valgrind, dar nu cred ca are legatura cu implementarea mea (dar cel mai probabil este pentru ca versiunea neoptimizata nu o are).

### Memory usage

```
BLAS: total heap usage: 80 allocs, 80 frees, 9,604,420 bytes allocated
Ne-optimizat: total heap usage: 11 allocs, 11 frees, 8,976,980 bytes allocated
Optimizat: total heap usage: 11 allocs, 11 frees, 8,976,980 bytes allocated
```

Deoarece la versiunea optimizatat am pornit de la cea neoptimizatat este acelasi memory usage. Interesant este ca cea cu blas are mai multe alocarii cu toate ca eu in functiia de solver am facut mai putine alocarii decat in celelalte versiuni. Presupun ca ATLAS faca alocarii in proprii.

## Results

```
Run=./tema3_blas: N=400: Time=0.026204
Run=./tema3_blas: N=800: Time=0.185223
Run=./tema3_blas: N=1000: Time=0.356111
Run=./tema3_blas: N=1200: Time=0.599831
Run=./tema3_blas: N=1600: Time=1.401712
```

```
Run=./tema3_neopt: N=400: Time=0.667189
Run=./tema3_neopt: N=800: Time=5.807836
Run=./tema3_neopt: N=1000: Time=9.865671
Run=./tema3_neopt: N=1200: Time=18.924393
Run=./tema3_neopt: N=1600: Time=69.081375
```

```
Run=./tema3_opt_m: N=400: Time=0.202658
Run=./tema3_opt_m: N=800: Time=1.429890
Run=./tema3_opt_m: N=1200: Time=4.785307
Run=./tema3_opt_m: N=1000: Time=2.798351
Run=./tema3_opt_m: N=1600: Time=11.314107
```

