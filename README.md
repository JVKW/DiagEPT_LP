# DiagEPT_LP - Sistema de Diagnóstico de Turmas EPT

Este é o primeiro projeto da disciplina de **Laboratório de Programação**, desenvolvido em linguagem **C**.

O objetivo é criar um sistema interativo para análise e diagnóstico de turmas da **Educação Profissional e Tecnológica (EPT)**, permitindo a organização de dados acadêmicos e avaliação de desempenho.

---

## 📌 Objetivo do Projeto

Desenvolver um programa que simule um sistema de gerenciamento contínuo através de um menu interativo, aplicando conceitos como:

- Estruturas de decisão
- Laços de repetição
- Validação de dados

---

## Diagrama de relacionamento entre entidades(structs)
```mermaid
erDiagram
    CURSO ||--o{ DISCIPLINA : contem
    DISCIPLINA ||--o{ TURMA : contem
    TURMA ||--|| DOCENTE : possui
    TURMA ||--o{ MATRICULA : possui
    MATRICULA ||--|| DISCENTE : contem
    MATRICULA ||--o| EVASAO : pode_ter

    CURSO {
        int id
        string nome
        string codigo
        int carga_horaria_total
    }
    DISCIPLINA {
        int id
        string nome
        string codigo
        int carga_horaria_total
    }

    TURMA {
        int id
        string periodo
    }

    DOCENTE {
        int id
        string nome
        string login
        string senha
    }

    MATRICULA {
        int id
        float nota_teorica
        float nota_pratica
        int aulas_assistidas
        int tempo_ausente
        int aulas_ausente
        bool tem_evasao
        string status
    }

    DISCENTE {
        int id
        string nome
        string ra
    }

    EVASAO {
        string motivo
    }

```

## ⚙️ Compilação

Para compilar o projeto, utilize o seguinte comando:

```bash
    gcc src/*.c src/*/*.c lib/cjson/cJSON.c -Iinclude -Iinclude/cjson -o bin/programa
    gcc (Get-ChildItem src/.c, src//*.c, lib/cjson/cJSON.c) -Iinclude -Iinclude/cjson -o bin/programa.exe
```
