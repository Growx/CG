Autor: Jean Carvalho Ortiz
A1
viewMatrix - O m�todo viewMatrix, define a Matrix de Vista do programa, definindo os versores de _matrix manualmente, realizando a decomposi��o de _rotation, assim extraindo o u,v e n que est�o armazenados em r[0],r[1] e r[2], respectivamente. Ap�s as adi��es a matriz, � realizado uma atualiza��o do _focalPoint realizando a soma da posi��o atual da c�mera com o produto do DOP e da dist�ncia.
inverseMatrix - utiliza-se de fun��o da mat4f para realizar a inversa da matriz _matrix. 
projectionMatrix - Definido os modos Perspection e Orthogonal, na qual no modo Perspection � preenchido a _projectionMatrix utilizando a fun��o perspective da mat4f, que tem como entrada o viewAngle, aspectRatio, F e B, onde a fun��o perspective realiza a constru��o da matriz. � adicionado ao valor de _matrix o resultado da opera��o lootAt, que retorna a matriz de visualiza��o e a matriz inversa.
Caso a visualiza��o seja ortogonal, � feito o c�lculo da largura da janela utilizando o aspectRatio * altura e a partir da largura � calculado o left e right, realizando a divis�o por dois da largura, sendo o left negativo. � feito tamb�m o c�lculo do bottom e top, utilizando a divis�o por dois da altura, sendo o bottom negativo. Ap�s os c�lculos, � adicionado a fun�ao ortho que ir� definir a matriz de proje��o.

updateFocalPoint - Fun��o extra criada para facilitar a atualiza��o do ponto focal. Essa fun��o recebe o focalpoint, position e distance e realiza o c�lcul: position - (versor de position - focalpoint) * distancia e executa a atualiza��o de visualiza��o.
A2
_setPosition - Feito a recep��o do valor em _position, ap�s isso � executado a atualiza��o do ponto focal, 	matriz de visualiza��o e inversa da matriz.
_setEulerAngle - Recebe o valor e salva em _eulerAngle e realiza a convers�o para radiano para ser salvo em _rotation.
_setRotation - Recebe o valor em _rotation, realiza a atualiza��o do ponto focal e da matriz de visualiza��o.
A3
setProjectionType - Define _projectType.
setDistance - Define o valor para _distance. Caso o valor seja maior que MIN_DISTANCE, o _distance assume o valor, caso contr�rio, o valor ser� MIN_DISTANCE que foi definido como 0.01. Realiza atualiza��o do Ponto focal
setViewAngle- Define o angulo de vis�o. Caso o valor seja maior que MIN_ANGLE, a variavel tempor�ria assume o valor, caso contr�rio ficar� como MIN_ANGLE. Caso o temp seja < MAX_ANGLE, _viewAngle ser� igual a temp, caso contr�rio, ser� MAX_ANGLE. � realizada a atualiza��o da matriz de proje��o.
setHeight - Define a altura da janela. caso o valor seja maior que MIN_HEIGHT, _height assume o valor. Caso contr�rio, o valor ser� MIN_HEIGH. � realizado a atualiza��o da matriz de proje��o.
setAspectRatio -  Define AspectRatio. caso o valor seja maior que MIN_ASPECT _aspectRatio assume o valor. Caso contr�rio, o valor ser� MIN_ASPECT. � realizado a atualiza��o da matriz de proje��o.
setClippingPlanes - Define a distancia dos planos de corte.
A4
zoom - Caso o tipo de proje��o seja Perspective, devinde o angulo de vis�o dividindo _viewAngle pelo valor do zoom. Caso contr�rio, divide o valor de _height pelo valor do zoom.
translate - Realiza a soma incremental do valor dx, dy em _posicao.x e _posicao.y e a subtra��o decremental em z.
rotateyx - Implementa��o n�o est� funcionando corretamente.
A5 - N�o implementado
A6
warcraft1.obj - https://www.thingiverse.com/thing:2025181 - Convertido de .stl para .obj pelo 3D Builder.
D.va_-_Thingiverse.obj - https://www.thingiverse.com/thing:2708937 - Convertido de .stl para .obj pelo 3D Builder.
