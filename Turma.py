import matplotlib.pyplot as plt 

num = int(input('Digite o número de alunos: '))
notas = [0.0]*num
maior = notas[0]
media = 0
for i in range(0,num):
    notas[i] = float(input('Digite a nota:'))
    while notas[i] > 10.0:
        print('Digite uma nota menor ou igual a 10.0')
        notas[i] = float(input('Digite a nota:'))
    if notas[i] > maior:
        maior = notas[i]
    media += notas[i]
media /= num 
print("Notas: ", notas)
print("Média da turma: ", media)
print("Maior nota da turma: ", maior)
print('Deseja visualizar um gráfico com a nota dos alunos? ')
print("Digite S para sim ")
print("Digite N para não ")
resp = input('Resposta: ')

if resp == 'S':
    fig, ax = plt.subplots()
    xbins = [0,5.0,6.0,7.0,8.0,9.0,10.0]
    ax = plt.hist(notas, bins = xbins, edgecolor = 'b')
    plt.show()
