# Controle-de-Nível

Lógica de Controle
O código principal opera em um loop infinito, onde três tarefas principais são executadas:
1. Atualização dos LEDs: Cada LED reflete diretamente o estado do botão correspondente. Quando um botão é pressionado, seu LED acende, e quando solto, o LED apaga.
2. Verificação das flags de acionamento do relé: Quando um botão dispara uma interrupção, sua respectiva flag (aciona_rele_btn1 ou aciona_rele_btn3) é ativada.
3. Acionamento do relé: Se uma flag estiver ativada, a função acionar_rele() é chamada, ligando o relé por 0,5 segundos e, em seguida, desligando-o.
