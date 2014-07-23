import subprocess

APPNAME = 'snake'
VERSION = '0.1'

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx')
    opt.add_option('--release', action='store', default=False,
                   help='Build release mode')

def configure(conf):
    conf.load('compiler_cxx')
    conf.env.CXXFLAGS = ['-std=c++11']
    print(conf.options.release)
    if conf.options.release == False:
        conf.env.append_value('CXXFLAGS', '-g')
    else:
        conf.env.LINKFLAGS = ['-mwindows']
        conf.env.append_value('CXXFLAGS', '-O2')

def build(bld):
    # build executable
    bld.program(source=bld.path.ant_glob('src/*.cpp'),
                target=APPNAME,
                lib=['mingw32', 'SDL2main', 'SDL2'],
                install_path='${PREFIX}/' + APPNAME + '/bin')

    # copy resources on install
    bld.install_files('${PREFIX}/' + APPNAME + '/resources',
                      bld.path.ant_glob('resources/*.bmp'))

def dist(dst):
    dst.algo = 'zip'

def run(ctx):
    subprocess.call(["build/snake"])
