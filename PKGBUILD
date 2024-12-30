# Maintainer: Natesworks <natesworks@natesworks.com>
pkgname=flatline
pkgver=1.0.0
pkgrel=1
pkgdesc="A library for handling CSV operations"
arch=('x86_64')
url="https://github.com/natesdev/flatline"
license=('MIT')
depends=()
makedepends=('gcc')
source=("$pkgname-$pkgver.tar.gz::$url/archive/refs/tags/v$pkgver.tar.gz")
sha256sums=('SKIP')

build() {
  cd "$srcdir/$pkgname-$pkgver"
  make
}

package() {
  cd "$srcdir/$pkgname-$pkgver"
  make DESTDIR="$pkgdir" install
  install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}
