set nocompatible                " choose no compatibility with legacy vi
syntax enable
set encoding=utf-8
set showcmd                     " display incomplete commands
filetype plugin indent on       " load file type plugins + indentation

"" Whitespace
set nowrap                      " don't wrap lines
set tabstop=2 shiftwidth=2      " a tab is two spaces (or set this to 4)
set expandtab                   " use spaces, not tabs (optional)
set backspace=indent,eol,start  " backspace through everything in insert mode

set list
set listchars=tab:»\ ,extends:›,precedes:‹,nbsp:·,trail:·

"" Searching
set hlsearch                    " highlight matches
set incsearch                   " incremental searching
set ignorecase                  " searches are case insensitive...
set smartcase                   " ... unless they contain at least one capital letter

set number
set relativenumber

"============VUNDLE===================="
set nocompatible
filetype off
set rtp+=$VIM/vimfiles/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'


" Add plugins here
Plugin 'tomasiser/vim-code-dark'
Plugin 'posva/vim-vue'
Plugin 'scrooloose/nerdcommenter'
Plugin 'Yggdroot/indentLine'


call vundle#end()
filetype plugin indent on

set t_Co=256
set t_ut=
colorscheme codedark

" set syntax highlight for .can(CAPL) file as .c file
" set syntax highlight for .dbc(CANoe data base) file as .xml file
augroup newfile_ext
  autocmd BufNewFile,BufRead *.dbc   set syntax=xml
  autocmd BufNewFile,BufRead *.can   set syntax=c
augroup END

"80 char margin
set colorcolumn=81
hi colorcolumn ctermbg=red guibg=red

" NERDcomment config
" ,ca : change to alt comment type
" ,ci : comment lines
" ,cs : comment beauty

let mapleader = ","
let NERDSpaceDelims=1

"autocmd VimEnter * LeadingSpaceEnable
let g:indentLine_color_term = 100
let g:indentLine_leadingSpaceEnabled = 1


