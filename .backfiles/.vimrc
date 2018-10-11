set nocompatible              " be iMproved, required
filetype off                  " required

"set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'
Plugin 'scrooloose/nerdtree'  "加入NERDTree，用于显示文件目录树
Plugin 'scrooloose/nerdcommenter'  "加入NERDCommenter，用于批量注释
Plugin 'nathanaelkane/vim-indent-guides'  "缩进可视化
Plugin 'Raimondi/delimitMate'  "括号等结对符自动补全

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
"-------------------------------------------------------------------------------------------


"vim 配置
"将<leader>设为';'
:let mapleader = ";"
"C/C++方式自动对齐
set autoindent
set cindent
"显示行号
set number
"设置匹配模式 类似当输入一个左括号时会匹配相应的那个右括号
"set showmatch
"设置搜索时忽略大小写
set ignorecase
"设置Tab宽度
set tabstop=4
"设置自动对齐空格数
set shiftwidth=4
"设置按退格键时可以一次删除4个空格
set softtabstop=4
"将Tab键自动转换成空格 真正需要Tab键时使用[Ctrl + V + Tab]
set expandtab
"针对不同的文件采用不同的缩进方式
filetype indent on
set smarttab
" 高亮显示当前行/列
set cursorline
set cursorcolumn


"YouCompleteMe配置
"YCM 补全菜单配色
" 菜单
"highlight Pmenu ctermfg=2 ctermbg=3 guifg=#005f87 guibg=#EEE8D5
" 选中项
highlight PmenuSel ctermfg=2 ctermbg=3 guifg=#AFD700 guibg=#106900
" 补全功能在注释中同样有效
let g:ycm_complete_in_comments=1
" 允许 vim 加载 .ycm_extra_conf.py 文件，不再提示
let g:ycm_confirm_extra_conf=0
" 开启 YCM 标签补全引擎
let g:ycm_collect_identifiers_from_tags_files=1
" 引入 C++ 标准库tags
"set tags+=/data/misc/software/misc./vim/stdcpp.tags
" YCM 集成 OmniCppComplete 补全引擎，设置其快捷键
"inoremap <leader>; <C-x><C-o>
" 补全内容不以分割子窗口形式出现，只显示补全列表
set completeopt-=preview
" 从第一个键入字符就开始罗列匹配项
let g:ycm_min_num_of_chars_for_completion=1
" 禁止缓存匹配项，每次都重新生成匹配项
let g:ycm_cache_omnifunc=0
" 语法关键字补全			
let g:ycm_seed_identifiers_with_syntax=1


"NERD Tree 文件树 配置
"强制自动打开NERDTree
autocmd vimenter * NERDTree
autocmd vimenter * NERDTreeClose
"当没有指定文件打开时，自动打开 NERDTree
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 0 && !exists("s:std_in") | NERDTree | endif
"关闭 vim 的时候如果只剩下 NERDTree, 那么自动关闭 NERDTree
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
"<F7> 打开/关闭 NERDTree
map <F7> :NERDTreeToggle<CR>

"NERD Commenter 批量注释 提示
"<leader>cc 注释当前行
"<leader>cm 只用一组符号来注释
"<leader>cy 注释并复制
"<leader>cs 优美的注释
"<leader>cu 取消注释


"indent-guides缩进可视化配置
" 随 vim 自启动
let g:indent_guides_enable_on_vim_startup=1
" 从第二层开始可视化显示缩进
let g:indent_guides_start_level=2
" 色块宽度
let g:indent_guides_guide_size=1
" 快捷键 i 开/关缩进可视化
:nmap <silent> <Leader>i <Plug>IndentGuidesToggle
