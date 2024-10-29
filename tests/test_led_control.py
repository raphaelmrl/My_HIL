import pytest
from pytest_embedded_idf import IdfDut

def test_On(dut: IdfDut):
    # Utilise une commande pour démarrer le firmware et observer la sortie
    dut.expect("LED On final")  # Attends la ligne dans le log qui indique que la LED clignote


def test_Off(dut: IdfDut):
    # Utilise une commande pour démarrer le firmware et observer la sortie
    dut.expect("LED Off final")  # Attends la ligne dans le log qui indique que la LED clignote