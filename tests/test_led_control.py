import pytest
from pytest_embedded_idf import IdfDut

def test_blink(dut: IdfDut):
    # Utilise une commande pour démarrer le firmware et observer la sortie
    dut.expect("LED On")  # Attends la ligne dans le log qui indique que la LED clignote
