set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'scrooloose/nerdtree'
Plugin 'taglist.vim'


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
" taglist configs
map <C-n> :NERDTreeToggle<CR>

" Backspace in Visual mode deletes selection.
vnoremap <BS> d

" CTRL-X are Cut.
vnoremap <C-X> "+x

" CTRL-C are Copy.
vnoremap <C-C> "+y

" CTRL-V are Paste.
map <C-V> "+gP
cmap <C-V> <C-R>+

" CTRL-Z is Undo; not in cmdline though.
noremap <C-Z> u
inoremap <C-Z> <C-O>u

" Pasting blockwise and linewise selections is not possible in Insert and Visual mode without the +virtualedit feature. They are pasted as if they were characterwise instead. Uses the paste.vim autoload script.
exe 'inoremap <script> <C-V>' paste#paste_cmd['i']
exe 'vnoremap <script> <C-V>' paste#paste_cmd['v']

"nerdtree configs
let Tlist_Use_Right_Window = 1

"taglist configs
nnoremap <silent> <F8> :TlistToggle<CR>
