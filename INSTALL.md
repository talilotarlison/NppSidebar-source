# Instalação do NppVim

O NppVim adiciona edição modal inspirada no Vim ao Notepad++. Para instalar, use uma versão do plugin compatível com a arquitetura do Notepad++ (32 ou 64 bits).

## Instalar pelo pacote do projeto

1. Feche completamente o Notepad++.
2. Na pasta de instalação do Notepad++, localize `plugins`. Se necessário, confira o caminho em **Configurações > Preferências > Pastas**.
3. Copie a pasta `NppVim` do pacote do plugin para `plugins`. Ela deve conter `NppVim.dll`. A estrutura esperada é:

   ```text
   <pasta do Notepad++>\plugins\NppVim\NppVim.dll
   ```

4. Abra o Notepad++ novamente e confira se **NppVim** aparece no menu **Plugins**.

> Se já houver uma instalação do NppVim, faça uma cópia de segurança antes de substituir os arquivos.

## Usar a DLL incluída neste repositório

Este repositório contém a DLL em `NppVim\NppVim.dll`. Copie a pasta `NppVim` para a pasta `plugins` do Notepad++, seguindo as etapas acima, e confirme que a DLL corresponde à arquitetura do aplicativo. Se não for compatível, obtenha uma versão adequada na página de releases do projeto.

## Primeiros passos

- Pressione `i` para entrar no modo de inserção.
- Pressione `Esc` para voltar ao modo normal.
- Pressione `:` para acessar o modo de comandos.
- Use `:help` ou `:h` para consultar a ajuda.

Consulte [NppVim/Readme.md](./NppVim/Readme.md) e a documentação em `NppVim/docs` para detalhes de uso e configuração.

## Desinstalar

Feche o Notepad++, remova a pasta `plugins\NppVim` e abra o aplicativo novamente.
