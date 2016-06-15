
Name:    rbutils
Version: %{__version}
Release: %{__release}%{?dist}

License: GNU AGPLv3
URL: https://github.com/redBorder/rbutils
Source0: %{name}-%{version}.tar.gz

BuildRequires: gcc librd-devel 

Summary: Util libraries for redborder C apps
Group:   Development/Libraries/C and C++
Requires: librd0

%description
%{summary}

%prep
%setup -qn %{name}-%{version}

%build
make

%install
DESTDIR=%{buildroot}/usr make install

%clean
rm -rf %{buildroot}

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%defattr(444,root,root)
/usr/include/librbutils
/usr/lib/librbutils.so
/usr/lib/librbutils.so.0
/usr/lib/librbutils.a

%changelog
* Wed May 11 2016 Juan J. Prieto <jjprieto@redborder.com> - 1.0.0-1
- first spec version


