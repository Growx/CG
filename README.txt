Autor: Jean Carvalho Ortiz
A1
viewMatrix - O método viewMatrix, define a Matrix de Vista do programa, definindo os versores de _matrix manualmente, realizando a decomposição de _rotation, assim extraindo o u,v e n que estão armazenados em r[0],r[1] e r[2], respectivamente. Após as adições a matriz, é realizado uma atualização do _focalPoint realizando a soma da posição atual da câmera com o produto do DOP e da distância.
inverseMatrix - utiliza-se de função da mat4f para realizar a inversa da matriz _matrix. 
projectionMatrix - Definido os modos Perspection e Orthogonal, na qual no modo Perspection é preenchido a _projectionMatrix utilizando a função perspective da mat4f, que tem como entrada o viewAngle, aspectRatio, F e B, onde a função perspective realiza a construção da matriz. É adicionado ao valor de _matrix o resultado da operação lootAt, que retorna a matriz de visualização e a matriz inversa.
Caso a visualização seja ortogonal, é feito o cálculo da largura da janela utilizando o aspectRatio * altura e a partir da largura é calculado o left e right, realizando a divisão por dois da largura, sendo o left negativo. É feito também o cálculo do bottom e top, utilizando a divisão por dois da altura, sendo o bottom negativo. Após os cálculos, é adicionado a funçao ortho que irá definir a matriz de projeção.

updateFocalPoint - Função extra criada para facilitar a atualização do ponto focal. Essa função recebe o focalpoint, position e distance e realiza o cálcul: position - (versor de position - focalpoint) * distancia e executa a atualização de visualização.
A2
_setPosition - Feito a recepção do valor em _position, após isso é executado a atualização do ponto focal, 	matriz de visualização e inversa da matriz.
_setEulerAngle - Recebe o valor e salva em _eulerAngle e realiza a conversão para radiano para ser salvo em _rotation.
_setRotation - Recebe o valor em _rotation, realiza a atualização do ponto focal e da matriz de visualização.
A3
setProjectionType - Define _projectType.
setDistance - Define o valor para _distance. Caso o valor seja maior que MIN_DISTANCE, o _distance assume o valor, caso contrário, o valor será MIN_DISTANCE que foi definido como 0.01. Realiza atualização do Ponto focal
setViewAngle- Define o angulo de visão. Caso o valor seja maior que MIN_ANGLE, a variavel temporária assume o valor, caso contrário ficará como MIN_ANGLE. Caso o temp seja < MAX_ANGLE, _viewAngle será igual a temp, caso contrário, será MAX_ANGLE. É realizada a atualização da matriz de projeção.
setHeight - Define a altura da janela. caso o valor seja maior que MIN_HEIGHT, _height assume o valor. Caso contrário, o valor será MIN_HEIGH. É realizado a atualização da matriz de projeção.
setAspectRatio -  Define AspectRatio. caso o valor seja maior que MIN_ASPECT _aspectRatio assume o valor. Caso contrário, o valor será MIN_ASPECT. É realizado a atualização da matriz de projeção.
setClippingPlanes - Define a distancia dos planos de corte.
A4
zoom - Caso o tipo de projeção seja Perspective, devinde o angulo de visão dividindo _viewAngle pelo valor do zoom. Caso contrário, divide o valor de _height pelo valor do zoom.
translate - Realiza a soma incremental do valor dx, dy em _posicao.x e _posicao.y e a subtração decremental em z.
rotateyx - Implementação não está funcionando corretamente.
A5 - Não implementado
A6
warcraft1.obj - https://www.thingiverse.com/thing:2025181 - Convertido de .stl para .obj pelo 3D Builder.
D.va_-_Thingiverse.obj - https://www.thingiverse.com/thing:2708937 - Convertido de .stl para .obj pelo 3D Builder.
