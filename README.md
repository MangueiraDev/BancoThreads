🧭 Visão Geral

O Banco Threads é um simulador de sistema bancário concorrente, desenvolvido em linguagem C com uso da biblioteca PThreads, que permite interações reais com o usuário via terminal e processa transações de forma simultânea com múltiplas threads servidoras.

O projeto aplica técnicas de controle de concorrência para garantir a segurança no acesso aos dados bancários em um ambiente multithread.

⸻

🎯 Objetivo do Projeto

Simular o funcionamento de um sistema bancário concorrente, onde um cliente interativo pode realizar:
	•	Depósitos
	•	Saques
	•	Consultas de extrato

As operações geram transações inseridas em uma fila compartilhada. Múltiplas threads servidoras consomem essas transações e atualizam os saldos das contas de forma segura e sincronizada.

⸻

⚙️ Como o sistema funciona
	•	O usuário interage com o sistema pelo terminal, escolhendo as operações desejadas.
	•	Cada operação gera uma transação bancária, que é armazenada em um buffer circular compartilhado.
	•	Threads servidoras retiram as transações da fila e processam cada uma de forma independente.
	•	O saldo de cada cliente é atualizado com segurança, mesmo com múltiplas threads acessando o sistema ao mesmo tempo.
	•	Logs são exibidos em tempo real no terminal, informando as ações realizadas.

⸻

🔐 Controle de Concorrência

O projeto é implementado em três versões independentes, cada uma com um mecanismo de sincronização:
	1.	Mutex — Exclusão mútua simples.
	2.	Semáforo — Controle da contagem de transações na fila.
	3.	Monitor (condição + mutex) — Coordenação entre produtor e consumidor com espera/sinalização.

⸻

📦 Componentes principais
	•	Cliente interativo: permite que o usuário escolha as operações via terminal.
	•	Fila de transações: buffer circular com capacidade limitada.
	•	Threads servidoras: processam as transações de forma concorrente.
	•	Banco de dados simulado: estrutura com os saldos das contas.
	•	Mecanismos de sincronização: garantem acesso seguro e ordenado aos dados.

⸻

✅ Requisitos do sistema
	•	Operações devem ser válidas e seguras (ex: saques sem saldo não são permitidos).
	•	A fila de transações deve ter capacidade limitada.
	•	As atualizações de saldo devem ser consistentes, mesmo sob concorrência.
	•	Logs devem ser exibidos para cada ação.

⸻

🛠️ Ambiente de Desenvolvimento
	•	Linguagem: C
	•	Biblioteca: POSIX Threads (PThreads)
	•	IDE: Visual Studio Code
	•	Plataforma: macOS com chip Apple M1 (arm64)

⸻

📁 Organização do Projeto
BancoThreads/                       # Raiz do projeto
├── .gitignore                      # Ignora arquivos desnecessários no controle de versão
├── README.md                       # Explicação geral do projeto e como executar
├── Makefile                        # Compila e executa diferentes versões (mutex, semáforo, monitor)
├── requirements.txt               # Dependências para compilar/executar (ex: gcc, make, pthreads)
├── include/                        # Arquivos de cabeçalho (.h)
│   ├── transaction.h
│   ├── account.h
│   └── queue.h
├── src/                            # Código-fonte do projeto
│   ├── main.c                      # Versão padrão (pode apontar para uma das sincronizações)
│   ├── mutex.c                     # Lógica com mutex
│   ├── semaphore.c                 # Lógica com semáforo
│   ├── monitor.c                   # Lógica com monitor (mutex + cond var)
│   ├── account.c                   # Operações de conta
│   ├── queue.c                     # Fila de transações
│   └── utils.c                     # Funções auxiliares (logs, geração de transações, etc.)
├── tests/                          # Casos de teste automatizados
│   └── basic_tests.c
└── .vscode/                        # Configurações do Visual Studio Code (opcional, mas útil)
    ├── settings.json              # Formatação automática e IntelliSense
    ├── tasks.json                 # Tarefas de build com gcc + -pthread
    └── launch.json                # Configuração de debug para Mac M1 (arm64)