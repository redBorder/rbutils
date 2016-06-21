%global libname rbutils

Name:    rbutils
Version: %{__version}
Release: %{__release}%{?dist}

License: GNU AGPLv3
URL: https://github.com/redBorder/rbutils
Source0: %{name}-%{version}.tar.gz

BuildRequires: gcc >= 4.1 librd-devel 

Summary: Util libraries for redborder C apps
Group:   Development/Libraries/C and C++
Requires: librd0
%description -n %{name}
%{summary}

%package -n %{name}-devel
Summary: Development files for %{name}
Group: Development/Libraries/C and C++
Requires: %{name} = %{version}-%{release}
%description -n %{name}-devel
%{summary}.

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

%files -n %{name}
%defattr(444,root,root)
/usr/lib/librbutils.so
/usr/lib/librbutils.so.0

%files -n %{name}-devel
%defattr(-,root,root)
%{_includedir}/librbutils
/usr/lib/librbutils.a


%changelog
* Tue Jun 21 2016 Alberto Rodriguez <arodriguez@redborder.com> - 1.0.0-1
- first spec version


