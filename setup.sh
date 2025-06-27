#!/bin/bash

echo "🧱 BancoThreads — Preparação do Ambiente"
echo "----------------------------------------"

# Verifica se gcc está instalado
echo "🔍 Verificando o compilador GCC..."
if ! command -v gcc &> /dev/null; then
    echo "❌ GCC não encontrado. Instalando Command Line Tools..."
    xcode-select --install
    echo "ℹ️ Após a instalação, execute este script novamente."
    exit 1
else
    echo "✅ GCC encontrado: $(gcc --version | head -n 1)"
fi

# Verifica se make está instalado
echo "🔍 Verificando o utilitário Make..."
if ! command -v make &> /dev/null; then
    echo "❌ Make não encontrado. Instale via 'xcode-select --install'"
    exit 1
else
    echo "✅ Make encontrado: $(make --version | head -n 1)"
fi

# Verifica se VS Code está instalado
echo "🔍 Verificando o Visual Studio Code..."
if ! command -v code &> /dev/null; then
    echo "⚠️ VS Code não encontrado no PATH. Você pode instalá-lo via: https://code.visualstudio.com/"
else
    echo "✅ VS Code detectado."
fi

# Conclusão
echo ""
echo "🎉 Ambiente verificado com sucesso!"
echo "➡️ Você pode agora compilar com: make banco_mutex"
echo "➡️ Ou abrir no VS Code com: code ."